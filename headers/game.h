#include <allegro5/allegro.h>

#include "ship.h"

#ifndef GAME_H
#define GAME_H

int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);

void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);

bool startGame(ALLEGRO_DISPLAY *display,
        ALLEGRO_EVENT_QUEUE *event_queue);

int spawnEnemy(Ship **array, int length, double timestamp);

void moveEnemy(const Ship hero, Ship *enemy);

#endif
