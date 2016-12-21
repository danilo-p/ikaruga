#include <allegro5/allegro.h>

#ifndef COMMON_H
#define COMMON_H

// Make game directions match with key directions. This makes simple the
// movimentation of the ships.
typedef enum {
    up = ALLEGRO_KEY_W,
    down = ALLEGRO_KEY_S,
    left = ALLEGRO_KEY_A,
    right = ALLEGRO_KEY_D
} direction;

typedef enum {
    alpha=0,
    gama,
} type;

void loginfo(const char *message);

void logerror(const char *message);

ALLEGRO_COLOR getTypeColor(type t);

#endif
