#include <allegro5/allegro.h>

#include "common.h"
#include "element.h"

#ifndef SHIP_H
#define SHIP_H

typedef struct {
    char id[255];
    direction course;
    Element shape;
    int bullet_count;
} Ship;

Ship createShip(char id[255], direction course, ALLEGRO_COLOR color);

bool checkShip(const Ship ship);

void renderShip(const Ship ship, ALLEGRO_DISPLAY *display);

void moveShip(Ship *ship, direction course);

bool destroyShip(Ship *ship);

bool checkShipsColision(const Ship ship_1, const Ship ship_2);

bool checkShipDisplayColision(const Ship ship);

void printShip(const Ship ship);

int pushShip(const Ship ship, Ship **array, int length);

#endif
