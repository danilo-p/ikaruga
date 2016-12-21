#include <allegro5/allegro.h>

#include "config.h"

const int FPS = 20;

const char* FONT_FAMILY = "roboto.ttf";
const int FONT_SIZE_SM = 15;
const int FONT_SIZE_MD = 20;
const int FONT_SIZE_LG = 30;

const int DISPLAY_WIDTH        = 500;
const int DISPLAY_HEIGHT       = 500;
const int DISPLAY_COLOR_RED    = 255;
const int DISPLAY_COLOR_GREEN  = 255;
const int DISPLAY_COLOR_BLUE   = 255;

const int SHIP_SIZE      = 30;
const int SHIP_STEP_SIZE = 10;
const double SHIP_FIRE_INTERVAL = 0.3;

const int BULLET_SIZE      = 5;
const int BULLET_STEP_SIZE = 15;

const int FIRST_ENEMY_OFFSET   = 0;
const int ENEMY_SPAWN_INTERVAL = 3;
const int ENEMY_STEP_SIZE      = 2;
const double ENEMY_FIRE_INTERVAL  = 1;

const int GAME_LEVEL_INTERVAL = 15;
const double GAME_LEVEL_DIFFICULTY_FACTOR = 2;
