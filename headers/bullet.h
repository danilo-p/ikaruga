#include <allegro5/allegro.h>

#include "element.h"
#include "ship.h"

#ifndef BULLET_H
#define BULLET_H

typedef struct {
    char id[255];
    direction course;
    type target;
    Ship *owner;
    Element capsule;
} Bullet;

Bullet createBullet(Ship *owner);

bool checkBullet(const Bullet bullet);

void renderBullet(const Bullet bullet, ALLEGRO_DISPLAY *display);

bool destroyBullet(Bullet *bullet);

void moveBullet(Bullet *bullet);

Bullet fireShip(Ship *ship, ALLEGRO_EVENT e);

bool checkBulletShipColision(const Bullet bullet, const Ship ship);

bool checkBulletDisplayColision(const Bullet bullet);

int pushBullet(const Bullet bullet, Bullet **array, int length);

int popBullet(const Bullet bullet, Bullet **array, int length);

void printBullet(const Bullet bullet);

void printBulletArray(const Bullet *array, int length);

#endif
