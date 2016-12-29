#include <allegro5/allegro.h>

#ifndef COMMON_H
#define COMMON_H

// The enum for the game directions, used to determine bullet and ship courses.
typedef enum {
    up = ALLEGRO_KEY_W, // Match with the W key code of the ALLEGRO lib
    down = ALLEGRO_KEY_S, // Match with the S key code of the ALLEGRO lib
    left = ALLEGRO_KEY_A, // Match with the A key code of the ALLEGRO lib
    right = ALLEGRO_KEY_D // Match with the D key code of the ALLEGRO lib
} direction;

// The enum for the game types, used to determine the bullet and ship targets
// and colors
typedef enum {
    alpha=0,
    gama,
} type;

// Print the message on the log format, with the time and a INFO label
void loginfo(const char *message);

// Print the message on the log format, with the time and a ERROR label
void logerror(const char *message);

// Return the correspondent color of the given type
ALLEGRO_COLOR getTypeColor(type t);

// Create the event queue and listen to the events of the keyboard and the given
// display and timer
ALLEGRO_EVENT_QUEUE * createEventQueue();

// Destroy the given allegro event queue
bool destroyEventQueue(ALLEGRO_EVENT_QUEUE **event_queue);

// Create and start a new allegro timer with the default config FPS
ALLEGRO_TIMER * createTimer();

// Destroy the given allegro timer
bool destroyTimer(ALLEGRO_TIMER **timer);

// Create the display with the default display dimensions
ALLEGRO_DISPLAY * createDisplay();

// Destroy the given display
bool destroyDisplay(ALLEGRO_DISPLAY **display);

#endif
