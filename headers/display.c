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

void renderDisplay(ALLEGRO_DISPLAY *display, int level, int score, double timestamp,
    ALLEGRO_FONT *size, int font_size) {
    // loginfo("renderDisplay enter");

    char score_text[255] = "", time_text[255] = "", level_text[255] = "";

    sprintf(score_text, "Score: %d", score);
    sprintf(time_text, "Time: %.2lf", timestamp);
    sprintf(level_text, "Level: %d", level);

    al_set_target_bitmap(al_get_backbuffer(display));

    if(size) {
        al_draw_text(size, al_map_rgb(0, 0, 0), 5, 5, 0, score_text);
        al_draw_text(size, al_map_rgb(0, 0, 0), 5, 10+font_size, 0, time_text);
        al_draw_text(size, al_map_rgb(0, 0, 0), 5, 30+font_size, 0, level_text);
    }

    al_flip_display();

    // loginfo("renderDisplay finish");
}
