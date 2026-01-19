#ifndef GRAVITY_BULLETS_H
#define GRAVITY_BULLETS_H

#include <stdint.h>
#include <stdio.h>
#include "defs.h"
#include "ship.h"
#include "sprites.h"

/*
    Fixed-point configuration:
    - We store position/velocity as integers with fractional part.
    - FP_SHIFT=8 => 1 cell = 256 units.
*/
#define FP_SHIFT 8
#define FP_ONE   (1 << FP_SHIFT)

/*
    Bullet state (no floats):
    - x_fp, y_fp: fixed-point position
    - vx_fp, vy_fp: fixed-point velocity (units per tick)
    - last_x/last_y: previous integer screen coordinates for erasing
*/
typedef struct {
    uint8_t alive;
    int32_t x_fp, y_fp;
    int32_t vx_fp, vy_fp;
    int16_t last_x, last_y;
} gbullet_t;

/*
    Gravity source (asteroid rectangle):
    - x,y: top-left corner
    - w,h: size (your asteroid is 6x5)
    - mu: gravity strength (integer). Tune visually.
*/
typedef struct {
    int16_t x, y;
    int16_t w, h;
    int32_t mu;
} grav_source_t;

// API
void gbullets_init(gbullet_t *b, int n);

void gbullet_spawn(gbullet_t *b, int n,
                   int16_t x, int16_t y,
                   int32_t vx_fp, int32_t vy_fp);

void gbullet_spawn_from_ship(gbullet_t *b, int n,
                             ship_coord_t sc, ship_size_t ss,
                             int32_t vx_fp, int32_t vy_fp);

/*
    One physics step + draw.
    dt_fp is fixed-point too:
    - dt_fp = FP_ONE means "one tick step".
    Keep it simple: pass dt_fp = FP_ONE.
*/
void gbullets_step_and_draw(gbullet_t *b, int n,
                            const grav_source_t *src, int src_n,
                            int32_t dt_fp);

// Auxiliary
int point_in_rect(int px, int py, int rx, int ry, int rw, int rh);

#endif
