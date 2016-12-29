#include <allegro5/allegro.h>

#include "element.h"
#include "ship.h"

#ifndef BULLET_H
#define BULLET_H

// Bullet structure
typedef struct {
    char id[255]; // Unique identifier
    direction course; // Bullet direction, called course
    type target; // Type of the bullet, called target
    Element capsule; // Element of the bullet, called capsule
} Bullet;

// Create a new bullet with the same course and type from the owner
Bullet createBullet(const Ship owner);

// Check if is a valid bullet (if it has a valid capsule and a valid id)
bool checkBullet(const Bullet bullet);

// Render the bullet capsule on the given display
void renderBullet(const Bullet bullet, ALLEGRO_DISPLAY *display);

// Destroy the bullet
bool destroyBullet(Bullet *bullet);

// Move the bullet capsule using the bullet course and the default step size
void moveBullet(Bullet *bullet);

// Create a new bullet for the given ship
Bullet fireShip(Ship *ship, double interval, ALLEGRO_EVENT e);

// Check if has a colision between a bullet and a ship
bool checkBulletShipColision(const Bullet bullet, const Ship ship);

// Check if has a colision between a bullet and the edges of the display
bool checkBulletDisplayColision(const Bullet bullet);

// Push a bullet into the given array and return the new length, making the
// necessary memory operations
int pushBullet(const Bullet bullet, Bullet **array, int length);

// Pop a bullet from the given array and return the new length, making the
// necessary memory operations and destroying the bullet if found
int popBullet(const Bullet bullet, Bullet **array, int length);

// Print the bullet formated info
void printBullet(const Bullet bullet);

// Print all the bullets from the given array
void printBulletArray(const Bullet *array, int length);

#endif
