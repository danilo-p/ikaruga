#include <allegro5/allegro.h>

#include "element.h"
#include "ship.h"

#ifndef BULLET_H
#define BULLET_H

typedef struct bullet {
    char id[255];
    direction course;
    Ship *owner;
    Element *capsule;
} Bullet;

Bullet * createBullet(Ship *owner);

void renderBullet(Bullet *bullet, ALLEGRO_DISPLAY *display);

void moveBullet(Bullet *bullet);

bool destroyBullet(Bullet *bullet);

Bullet * fireShip(Ship *ship);

void pushBullet(Bullet *bullet, Bullet **array, int array_lenght);

int popBullet(Bullet *bullet, Bullet *array, int array_lenght);

#endif
