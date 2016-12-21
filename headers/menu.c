#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "menu.h"
#include "display.h"
#include "config.h"
#include "common.h"

int mainMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue) {

    loginfo("mainMenu enter");

    int option = -1;
    char title_text[] = "I K A R U G A", enter_text[] = "Pressione enter para iniciar...";
    ALLEGRO_FONT *size_lg = NULL, *size_md = NULL;

    size_lg = al_load_font(FONT_FAMILY, FONT_SIZE_LG, 1);
    size_md = al_load_font(FONT_FAMILY, FONT_SIZE_MD, 1);
    if(!size_lg || !size_md) {
        logerror("Failed to load font");
        return 0;
    }

    clearDisplay(display);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_text(
        size_lg,
        al_map_rgb(0, 0, 0),
        (DISPLAY_WIDTH/2.0),
        DISPLAY_HEIGHT/3,
        ALLEGRO_ALIGN_CENTRE,
        title_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(0, 0, 0),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD,
        ALLEGRO_ALIGN_CENTRE,
        enter_text
    );

    al_flip_display();

    while(option < 0) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN &&
            e.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            option++;
        }
    }

    loginfo("mainMenu finish");

    return option;
}
