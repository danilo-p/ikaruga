#include <allegro5/allegro.h>

#include "ship.h"

#ifndef GAME_H
#define GAME_H

ALLEGRO_EVENT_QUEUE * createEventQueue();

bool destroyEventQueue(ALLEGRO_EVENT_QUEUE **event_queue);

ALLEGRO_TIMER * createTimer();

bool destroyTimer(ALLEGRO_TIMER **timer);

bool initGame();

// void destroyGame(ALLEGRO_DISPLAY **display);

bool startGame(ALLEGRO_DISPLAY *display);

int spawnEnemy(Ship **array, int length, double timestamp);

void moveEnemy(const Ship hero, Ship *enemy);

#endif
