#include <allegro5/allegro.h>

#include "config.h"

const int FPS = 20;

const int DISPLAY_WIDTH        = 500;
const int DISPLAY_HEIGHT       = 500;
const int DISPLAY_COLOR_RED    = 255;
const int DISPLAY_COLOR_GREEN  = 255;
const int DISPLAY_COLOR_BLUE   = 255;

const int SHIP_SIZE      = 30;
const int SHIP_STEP_SIZE = 10;
const double SHIP_FIRE_INTERVAL = 0.3;

const int TYPE_1_RED   = 255;
const int TYPE_1_GREEN = 0;
const int TYPE_1_BLUE  = 0;

const int TYPE_2_RED   = 0;
const int TYPE_2_GREEN = 0;
const int TYPE_2_BLUE  = 255;

const int BULLET_SIZE      = 5;
const int BULLET_STEP_SIZE = 15;

const int FIRST_ENEMY_OFFSET   = 3;
const int ENEMY_SPAWN_INTERVAL = 1;
