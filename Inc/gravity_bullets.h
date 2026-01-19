/*
 * gravity_bullets.h
 *
 *  Created on: 19 Jan 2026
 *      Author: root
 */

#ifndef GRAVITY_BULLETS_H
#define GRAVITY_BULLETS_H

#include <stdint.h>

#ifndef MAXBULLETS
#define MAXBULLETS 16
#endif

//Visible area boundaries (terminal coordinates: x=column, y=row)
#ifndef X1
#define X1 2
#endif
#ifndef Y1
#define Y1 2
#endif
#ifndef X2
#define X2 170
#endif
#ifndef Y2
#define Y2 50
#endif

// Types
typedef struct {
    uint8_t alive;
    float x, y;       // position
    float vx, vy;     // speed
    int last_x, last_y; // past integer coordinates to erase
} gbullet_t;

// Gravity source (6x5 asteroid)
typedef struct {
    int x, y;       // top left corner (like asteroid_sprite)
    int w, h;       // rectangle dimensions (for your asteroid: 6.5)
    float mu;       // "force" (G*M). Selected visually.
} grav_source_t;

// API
void gbullets_init(gbullet_t *b, int n);

void gbullet_spawn(gbullet_t *b, int n,
                   float x, float y,
                   float vx, float vy);

// bullet position in front of the ship's bow
#include "ship.h"
#include "sprites.h"
void gbullet_spawn_from_ship(gbullet_t *b, int n,
                             ship_coord_t sc, ship_size_t ss,
                             float vx, float vy);

// One physics step + rendering of all bullets
void gbullets_step_and_draw(gbullet_t *b, int n,
                            const grav_source_t *src, int src_n,
                            float dt);

// Auxiliary: point in rectangle
int point_in_rect(int px, int py, int rx, int ry, int rw, int rh);

#endif
