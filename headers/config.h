#include <allegro5/allegro.h>

#ifndef CONFIG_H
#define CONFIG_H

// Game FPS
const int FPS;

// Where the best score is stored
const char* SCORE_FILE;

// The font family file. Must be ttf formated.
const char* FONT_FAMILY;

// The font sizes
const int FONT_SIZE_SM; // pixels
const int FONT_SIZE_MD; // pixels
const int FONT_SIZE_LG; // pixels

// The display dimensions
const int DISPLAY_WIDTH; // pixels
const int DISPLAY_HEIGHT; // pixels

// The ship dimensions, step size and fire currency
const int SHIP_SIZE; // pixels
const int SHIP_STEP_SIZE; // pixels
const double SHIP_FIRE_INTERVAL; // seconds

// The bullet dimensions and step size
const int BULLET_SIZE; // pixels
const int BULLET_STEP_SIZE; // pixels

// The delay for displaying the first enemy
const int FIRST_ENEMY_OFFSET; // seconds
// The interval for displaying enemies
const int ENEMY_SPAWN_INTERVAL; // seconds
// Enemy step size
const int ENEMY_STEP_SIZE;
// Enemy fire interval
const double ENEMY_FIRE_INTERVAL;

// The interval for the levels
const int GAME_LEVEL_INTERVAL; // seconds
// The ammount of difficulty increased on each level. The higher the number, the
// higher difficulty.
const double GAME_LEVEL_DIFFICULTY_FACTOR; // number

#endif
