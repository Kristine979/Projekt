#ifndef ASTROID_H_
#define ASTROID_H_

#include <stdint.h>

/* Asteroid */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t color;
    int8_t  speed;
    int8_t  active;
    uint16_t rng;      // pseudo-random state (lokal)
} astroid_t;

/* Controller (erstatter static/global timer) */
typedef struct {
    int16_t spawn_timer;
    int16_t spawn_interval;
} astroid_ctrl_t;

void astroid_init(astroid_t *a, int16_t x, int16_t y, int16_t color, int8_t speed);

void astroid_update(astroid_t *a);
void astroid_draw(const astroid_t *a);

void astroid_spawn(astroid_t astroids[], int max_astroids, astroid_ctrl_t *ctrl, int16_t start_x, int16_t color, int8_t speed);

#endif /* ASTROID_H_ */
