#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "common.h"

#ifndef DISPLAY_H
#define DISPLAY_H

// Clear the display with the given color
void clearDisplay(ALLEGRO_DISPLAY *display, ALLEGRO_COLOR display_color);

// Render the game display marks like score, time and options
void renderGameDisplay(ALLEGRO_DISPLAY *display, int level, int score,
    double timestamp, ALLEGRO_FONT *size, int font_size);

#endif
