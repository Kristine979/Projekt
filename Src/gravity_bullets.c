#include "gravity_bullets.h"

#ifndef ESC
#define ESC 0x1B
#endif

// TUNING
#define BULLET_CHAR   'O'

// Softening: larger => softer near asteroid (less sudden jerks)
// Units are "cells^2"
#define SOFTEN_R2     (9*9)

// Very light damping (1.0 = off) but in integer form
// vx = vx * DAMP_NUM / DAMP_DEN
#define DAMP_NUM      999
#define DAMP_DEN      1000

// Cutoff: gravity only applies within a radius GRAV_RMAX from asteroid
// Units are "cells"
#define GRAV_RMAX     8
#define GRAV_RMAX2    (GRAV_RMAX * GRAV_RMAX)

// PLAY AREA (protect the frame)
// Bullets will never be erased on the frame itself
#define PLAY_X1 (X1 + 1)
#define PLAY_X2 (X2 - 1)
#define PLAY_Y1 (Y1 + 1)
#define PLAY_Y2 (Y2 - 1)

// helpers

static void draw_char_at(int x, int y, char c) {
    if (x < PLAY_X1 || x > PLAY_X2 || y < PLAY_Y1 || y > PLAY_Y2) return;
    printf("%c[%d;%dH%c", ESC, y, x, c);
}

int point_in_rect(int px, int py, int rx, int ry, int rw, int rh) {
    return (px >= rx) && (px < rx + rw) && (py >= ry) && (py < ry + rh);
}

/*
    Integer "gravity-like" acceleration without sqrt and without floats.

    We compute:
        r2 = dx*dx + dy*dy
        ax_fp += (mu * dx * FP_ONE) / r2
        ay_fp += (mu * dy * FP_ONE) / r2

    This is not the exact 1/r^3 law, but it looks like gravity and is cheap on MCU.
*/
static void gravity_accel_at(const gbullet_t *p,
                             const grav_source_t *src, int src_n,
                             int32_t *out_ax_fp, int32_t *out_ay_fp)
{
    int32_t ax_fp = 0;
    int32_t ay_fp = 0;

    // Current bullet position in integer cells
    int32_t px = (p->x_fp >> FP_SHIFT);
    int32_t py = (p->y_fp >> FP_SHIFT);

    for (int i = 0; i < src_n; i++) {
        // Rectangle center (asteroid)
        int32_t cx = (int32_t)src[i].x + (src[i].w / 2);
        int32_t cy = (int32_t)src[i].y + (src[i].h / 2);

        int32_t dx = cx - px;
        int32_t dy = cy - py;

        int32_t r2 = dx*dx + dy*dy;

        // 1) cutoff: if far away, no effect
        if (r2 > GRAV_RMAX2) continue;

        // 2) softening: if too close, limit force
        if (r2 < SOFTEN_R2) r2 = SOFTEN_R2;

        // ax_fp += (mu * dx * FP_ONE) / r2
        ax_fp += (int32_t)((src[i].mu * dx * FP_ONE) / r2);
        ay_fp += (int32_t)((src[i].mu * dy * FP_ONE) / r2);
    }

    *out_ax_fp = ax_fp;
    *out_ay_fp = ay_fp;
}

void gbullets_init(gbullet_t *b, int n) {
    for (int i = 0; i < n; i++) {
        b[i].alive = 0;
        b[i].x_fp = 0;
        b[i].y_fp = 0;
        b[i].vx_fp = 0;
        b[i].vy_fp = 0;
        b[i].last_x = -9999;
        b[i].last_y = -9999;
    }
}

void gbullet_spawn(gbullet_t *b, int n, int16_t x, int16_t y, int32_t vx_fp, int32_t vy_fp)
{
    for (int i = 0; i < n; i++) {
        if (!b[i].alive) {
            b[i].alive = 1;

            // Store position in fixed-point
            b[i].x_fp = ((int32_t)x) << FP_SHIFT;
            b[i].y_fp = ((int32_t)y) << FP_SHIFT;

            // Store velocity in fixed-point (units per tick)
            b[i].vx_fp = vx_fp;
            b[i].vy_fp = vy_fp;

            b[i].last_x = x;
            b[i].last_y = y;

            // Draw initial bullet
            draw_char_at(b[i].last_x, b[i].last_y, BULLET_CHAR);
            return;
        }
    }
}

void gbullet_spawn_from_ship(gbullet_t *b, int n,
                             ship_coord_t sc, ship_size_t ss,
                             int32_t vx_fp, int32_t vy_fp)
{
    int16_t start_x = (int16_t)(sc.x + ss.l + 1);
    int16_t start_y = (int16_t)(sc.y + 1);
    gbullet_spawn(b, n, start_x, start_y, vx_fp, vy_fp);
}

void gbullets_step_and_draw(gbullet_t *b, int n,
                            const grav_source_t *src, int src_n,
                            int32_t dt_fp)
{
    for (int i = 0; i < n; i++) {
        if (!b[i].alive) continue;

        // 1) acceleration due to gravity (fixed-point)
        int32_t ax_fp = 0, ay_fp = 0;
        gravity_accel_at(&b[i], src, src_n, &ax_fp, &ay_fp);

        // 2) speed update: v += a * dt
        // dt_fp is fixed-point. Multiply then shift back.
        b[i].vx_fp += (ax_fp * dt_fp) >> FP_SHIFT;
        b[i].vy_fp += (ay_fp * dt_fp) >> FP_SHIFT;

        // Integer damping (optional)
        b[i].vx_fp = (b[i].vx_fp * DAMP_NUM) / DAMP_DEN;
        b[i].vy_fp = (b[i].vy_fp * DAMP_NUM) / DAMP_DEN;

        // 3) position update: x += v * dt
        b[i].x_fp += (b[i].vx_fp * dt_fp) >> FP_SHIFT;
        b[i].y_fp += (b[i].vy_fp * dt_fp) >> FP_SHIFT;

        // Convert to integer screen cells (rounded)
        int xi = (int)((b[i].x_fp + (FP_ONE/2)) >> FP_SHIFT);
        int yi = (int)((b[i].y_fp + (FP_ONE/2)) >> FP_SHIFT);

        // 4) If it flies out of the playing field (inside the frame)
        if (xi < PLAY_X1 || xi > PLAY_X2 || yi < PLAY_Y1 || yi > PLAY_Y2) {
            draw_char_at(b[i].last_x, b[i].last_y, ' ');
            b[i].alive = 0;
            continue;
        }

        // 5) Asteroid collision - extinguish the bullet
        for (int s = 0; s < src_n; s++) {
            if (point_in_rect(xi, yi, src[s].x, src[s].y, src[s].w, src[s].h)) {
                draw_char_at(b[i].last_x, b[i].last_y, ' ');
                b[i].alive = 0;
                break;
            }
        }
        if (!b[i].alive) continue;

        // 6) drawing
        if (xi != b[i].last_x || yi != b[i].last_y) {
            draw_char_at(b[i].last_x, b[i].last_y, ' ');
            draw_char_at(xi, yi, BULLET_CHAR);
            b[i].last_x = xi;
            b[i].last_y = yi;
        }
    }
}
