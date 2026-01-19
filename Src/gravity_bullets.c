#include "gravity_bullets.h"
#include <stdio.h>
#include <math.h>

#ifndef ESC
#define ESC 0x1B
#endif

//TUNING
#define BULLET_CHAR   'O'

// Softening: the higher the value, the softer it is near the asteroid (less sudden jerks)
#define SOFTEN_R2     81.0f

// Very light damping (1.0f = off)
#define DAMPING       0.999f

//// Cutoff: gravity only applies within a radius of GRAV_RMAX from the asteroid
#define GRAV_RMAX     8.0f
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

static void gravity_accel_at(const gbullet_t *p,
                             const grav_source_t *src, int src_n,
                             float *out_ax, float *out_ay)
{
    float ax = 0.0f, ay = 0.0f;

    for (int i = 0; i < src_n; i++) {
    	// rectangle center (asteroid))
        float cx = (float)src[i].x + (float)src[i].w * 0.5f;
        float cy = (float)src[i].y + (float)src[i].h * 0.5f;

        float dx = cx - p->x;
        float dy = cy - p->y;

        float r2 = dx*dx + dy*dy;

        // 1) cutoff: if it's far away, it doesn't affect anything
        if (r2 > GRAV_RMAX2) continue;

        // 2) softening: if it's too close, we limit the force
        if (r2 < SOFTEN_R2) r2 = SOFTEN_R2;

        // a = mu * r_vec / |r|^3
        float inv_r = 1.0f / sqrtf(r2);
        float inv_r3 = inv_r * inv_r * inv_r;

        ax += src[i].mu * dx * inv_r3;
        ay += src[i].mu * dy * inv_r3;
    }

    *out_ax = ax;
    *out_ay = ay;
}

// public API
void gbullets_init(gbullet_t *b, int n) {
    for (int i = 0; i < n; i++) {
        b[i].alive = 0;
        b[i].x = b[i].y = 0.0f;
        b[i].vx = b[i].vy = 0.0f;
        b[i].last_x = b[i].last_y = -9999;
    }
}

void gbullet_spawn(gbullet_t *b, int n, float x, float y, float vx, float vy)
{
    for (int i = 0; i < n; i++) {
        if (!b[i].alive) {
            b[i].alive = 1;
            b[i].x = x;
            b[i].y = y;
            b[i].vx = vx;
            b[i].vy = vy;

            b[i].last_x = (int)lroundf(x);
            b[i].last_y = (int)lroundf(y);

            // Draw only inside the field (the frame will not be affected)
            draw_char_at(b[i].last_x, b[i].last_y, BULLET_CHAR);
            return;
        }
    }
}

void gbullet_spawn_from_ship(gbullet_t *b, int n,
                             ship_coord_t sc, ship_size_t ss,
                             float vx, float vy)
{
    float start_x = (float)(sc.x + ss.l + 1);
    float start_y = (float)(sc.y + 1);
    gbullet_spawn(b, n, start_x, start_y, vx, vy);
}

void gbullets_step_and_draw(gbullet_t *b, int n,
                            const grav_source_t *src, int src_n,
                            float dt)
{
    for (int i = 0; i < n; i++) {
        if (!b[i].alive) continue;

        // 1) acceleration due to gravity
        float ax = 0.0f, ay = 0.0f;
        gravity_accel_at(&b[i], src, src_n, &ax, &ay);

        // --- 2) speed
        b[i].vx += ax * dt;
        b[i].vy += ay * dt;

        b[i].vx *= DAMPING;
        b[i].vy *= DAMPING;

        // --- 3) position
        b[i].x += b[i].vx * dt;
        b[i].y += b[i].vy * dt;

        int xi = (int)lroundf(b[i].x);
        int yi = (int)lroundf(b[i].y);

        // 4) If it flies out of the playing field (inside the frame)
        if (xi < PLAY_X1 || xi > PLAY_X2 || yi < PLAY_Y1 || yi > PLAY_Y2) {
            //We erase only if the previous point was inside the field.
            draw_char_at(b[i].last_x, b[i].last_y, ' ');
            b[i].alive = 0;
            continue;
        }

        // 5)Asteroid collision - extinguish the bullet
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
