#include <allegro5/allegro.h>

#include "ship.h"

#ifndef GAME_H
#define GAME_H

// Init the allegro library, keyboard and required addons for the game
bool initGame();

// Start the game. This is the place where the magic happens.
bool startGame(ALLEGRO_DISPLAY *display);

// Spawn a new enemy on the game by pushing a new ship on the given array.
int spawnEnemy(Ship **array, int length, double timestamp);

// Move the enemy according to the hero position
void moveEnemy(const Ship hero, Ship *enemy);

#endif
