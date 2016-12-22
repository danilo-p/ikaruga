#include <allegro5/allegro.h>

#include "common.h"

#ifndef DISPLAY_H
#define DISPLAY_H

void clearDisplay(ALLEGRO_DISPLAY *display);

void renderGameDisplay(ALLEGRO_DISPLAY *display, int level, int score,
    double timestamp, ALLEGRO_FONT *size, int font_size);

#endif
