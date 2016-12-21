#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "display.h"


void clearDisplay(ALLEGRO_DISPLAY *display) {
    // loginfo("clearDisplay enter");

    ALLEGRO_COLOR display_color = al_map_rgb(
        DISPLAY_COLOR_RED,
        DISPLAY_COLOR_GREEN,
        DISPLAY_COLOR_BLUE
    );

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(display_color);

    // loginfo("clearDisplay finish");
}

void renderDisplay(ALLEGRO_DISPLAY *display, int score, double timestamp) {
    // loginfo("renderDisplay enter");

    ALLEGRO_FONT *size = al_load_font("arial.ttf", 15, 1);
    char score_text[255] = "", time_text[255] = "";

    sprintf(score_text, "Score: %d", score);
    sprintf(time_text, "Time: %.2lf", timestamp);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_text(size, al_map_rgb(0, 0, 0), 5, 5, 0, score_text);
    al_draw_text(size, al_map_rgb(0, 0, 0), 5, 25, 0, time_text);

    al_flip_display();

    // loginfo("renderDisplay finish");
}
