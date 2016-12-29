#include <allegro5/allegro.h>

#include "common.h"
#include "element.h"

#ifndef SHIP_H
#define SHIP_H

// Ship structure
typedef struct {
    char id[255]; // Unique identifier
    direction course; // Ship direction, called course
    type target; // Ship type, called target
    Element shape; // Element of the ship, called shape
    double last_bullet_fired; // Moment of the last bullet fired
    int bullet_count; // Amount of bullets fired
} Ship;

// Create a new ship with the given parameters
Ship createShip(char id[255], int x, int y, direction course, type target);

// Set the ship target
void setShipTarget(Ship *ship, type target);

// Check if is a valid ship (if it has a valid shape and a valid id)
bool checkShip(const Ship ship);

// Render the ship capsule on the given display
void renderShip(const Ship ship, ALLEGRO_DISPLAY *display);

// Move the ship shape using the given direction and the step size
void moveShip(Ship *ship, direction course, int step_size);

// Destroy the ship
bool destroyShip(Ship *ship);

// Check if has a colision between two ships
bool checkShipsColision(const Ship ship_1, const Ship ship_2);

// Check if has a colision between a ship and the edges of the display
bool checkShipDisplayColision(const Ship ship);

// Print the ship formated info
void printShip(const Ship ship);

// Print all the ships from the given array
void printShipArray(const Ship *array, int length);

// Push a ship into the given array and return the new length, making the
// necessary memory operations
int pushShip(const Ship ship, Ship **array, int length);

// Pop a ship from the given array and return the new length, making the
// necessary memory operations and destroying the ship if found
int popShip(const Ship ship, Ship **array, int length);

#endif
