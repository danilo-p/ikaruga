#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "display.h"


void clearDisplay(ALLEGRO_DISPLAY *display) {
    // loginfo("clearDisplay enter");

    ALLEGRO_COLOR display_color = al_map_rgb(0, 0, 0);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(display_color);

    // loginfo("clearDisplay finish");
}

void renderGameDisplay(ALLEGRO_DISPLAY *display, int level, int score,
        double timestamp, ALLEGRO_FONT *size, int font_size) {
    // loginfo("renderDisplay enter");

    char score_text[255] = "";
    char time_text[255] = "";
    char level_text[255] = "";
    char pause_text[] = "P - Pause";

    sprintf(score_text, "Score: %d", score);
    sprintf(time_text, "Time: %.2lf", timestamp);
    sprintf(level_text, "Level: %d", level);

    al_set_target_bitmap(al_get_backbuffer(display));

    if(size) {
        al_draw_text(size, al_map_rgb(255, 255, 255), 5, 5, ALLEGRO_ALIGN_LEFT, score_text);
        al_draw_text(size, al_map_rgb(255, 255, 255), 5, 10+font_size, ALLEGRO_ALIGN_LEFT, time_text);
        al_draw_text(size, al_map_rgb(255, 255, 255), 5, 30+font_size, ALLEGRO_ALIGN_LEFT, level_text);
        al_draw_text(size, al_map_rgb(255, 255, 255), DISPLAY_WIDTH-5, 5, ALLEGRO_ALIGN_RIGHT, pause_text);
    }

    al_flip_display();

    // loginfo("renderDisplay finish");
}
