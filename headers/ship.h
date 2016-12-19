#include <allegro5/allegro.h>

#include "common.h"
#include "element.h"

#ifndef SHIP_H
#define SHIP_H

struct ship;
typedef struct ship {
    char id[255];
    direction course;
    Element *shape;
    int bullet_count;
} Ship;

Ship * createShip(char id[255], direction course, ALLEGRO_COLOR color);

void renderShip(Ship *ship, ALLEGRO_DISPLAY *display);

void moveShip(Ship *ship, direction course);

bool destroyShip(Ship *ship);

#endif
