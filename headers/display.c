#include <allegro5/allegro.h>

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

void renderDisplay(ALLEGRO_DISPLAY *display) {
    // loginfo("renderDisplay enter");

    al_set_target_bitmap(al_get_backbuffer(display));
    al_flip_display();

    // loginfo("renderDisplay finish");
}
