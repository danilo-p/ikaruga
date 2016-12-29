#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "common.h"

#ifndef DISPLAY_H
#define DISPLAY_H

ALLEGRO_DISPLAY * createDisplay();

bool destroyDisplay(ALLEGRO_DISPLAY **display);

void clearDisplay(ALLEGRO_DISPLAY *display, ALLEGRO_COLOR display_color);

void renderGameDisplay(ALLEGRO_DISPLAY *display, int level, int score,
    double timestamp, ALLEGRO_FONT *size, int font_size);

#endif
