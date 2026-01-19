#include "Astroid.h"
#include "sprites.h"
#include "ansi.h"
#include <stdio.h>

#define ASTROID_HEIGHT  5
#define SCREEN_LEFT     1
#define ASTROID_Y_MIN   5
#define ASTROID_Y_MAX   30

/* ---------- interne hjælpefunktioner ---------- */

static void astroid_clear(const astroid_t *a)
{
    int i;
    for (i = 0; i < ASTROID_HEIGHT; i++) {
        printf("%c[%d;%dH      ", ESC, a->y + i, a->x);
    }
}

/* xorshift RNG – ingen /, %, globals */
static uint16_t astroid_rng_next(uint16_t *state)
{
    uint16_t x = *state;
    x ^= x << 7;
    x ^= x >> 9;
    x ^= x << 8;
    *state = x;
    return x;
}

/* ---------- offentlige funktioner ---------- */

void astroid_init(astroid_t *a, int16_t x, int16_t y,
                  int16_t color, int8_t speed)
{
    a->x = x;
    a->y = y;
    a->color = color;
    a->speed = speed;
    a->active = 1;

    /* seed RNG (ingen konstant, ingen globals) */
    a->rng = (uint16_t)(x ^ (y << 3));
    if (a->rng == 0) {
        a->rng = 1;
    }
}

void astroid_update(astroid_t *a)
{
    if (a->active == 0) return;

    astroid_clear(a);
    a->x -= a->speed;

    if (a->x <= SCREEN_LEFT) {
        a->active = 0;
    }
}

void astroid_draw(const astroid_t *a)
{
    if (a->active == 0) return;
    asteroid_sprite(a->color, a->x, a->y);
}

void astroid_spawn(astroid_t astroids[], int max_astroids,
                   astroid_ctrl_t *ctrl,
                   int16_t start_x, int16_t color, int8_t speed)
{
    int i;
    uint16_t r;
    int16_t y;

    /* timer styres her – ingen static/global */
    ctrl->spawn_timer++;
    if (ctrl->spawn_timer < ctrl->spawn_interval)
        return;

    ctrl->spawn_timer = 0;

    for (i = 0; i < max_astroids; i++) {
        if (astroids[i].active == 0) {

            /* pseudo-random y uden / og % */
            r = astroid_rng_next(&astroids[i].rng);
            y = ASTROID_Y_MIN + (r & 0x1F);   // 0–31 via bitmask
            if (y > ASTROID_Y_MAX)
                y = ASTROID_Y_MAX;

            astroid_init(&astroids[i],
                         start_x,
                         y,
                         color,
                         speed);
            break;  // kun én spawn
        }
    }
}
