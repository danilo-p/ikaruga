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
    char title_text[] = "I K A R U G A";
    char play_text[] = "ENTER - Play";
    char quit_text[] = "Q - Quit";
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
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        DISPLAY_HEIGHT/3,
        ALLEGRO_ALIGN_CENTRE,
        title_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD,
        ALLEGRO_ALIGN_CENTRE,
        play_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD + FONT_SIZE_LG,
        ALLEGRO_ALIGN_CENTRE,
        quit_text
    );

    al_flip_display();

    while(option < 0) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    option = 1;
                break;
                case ALLEGRO_KEY_Q:
                    option = 0;
                break;
            }
        }
    }

    loginfo("mainMenu finish");

    return option;
}

int pauseMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue) {

    loginfo("pauseMenu enter");

    int option = -1;
    char title_text[] = "Game paused";
    char play_text[] = "ENTER - Continue";
    char quit_text[] = "Q - Quit";
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
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        DISPLAY_HEIGHT/3,
        ALLEGRO_ALIGN_CENTRE,
        title_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD,
        ALLEGRO_ALIGN_CENTRE,
        play_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD + FONT_SIZE_LG,
        ALLEGRO_ALIGN_CENTRE,
        quit_text
    );

    al_flip_display();

    while(option < 0) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    option = 1;
                break;
                case ALLEGRO_KEY_Q:
                    option = 0;
                break;
            }
        }
    }

    loginfo("pauseMenu finish");

    return option;
}

int gameFinishedMenu(ALLEGRO_DISPLAY *display, int score, double time_elapsed) {
    loginfo("gameFinishedMenu enter");

    char title_text[] = "You lose";
    char score_text[255] = "";
    char time_text[255] = "";
    ALLEGRO_FONT *size_lg = NULL, *size_md = NULL;

    size_lg = al_load_font(FONT_FAMILY, FONT_SIZE_LG, 1);
    size_md = al_load_font(FONT_FAMILY, FONT_SIZE_MD, 1);
    if(!size_lg || !size_md) {
        logerror("Failed to load font");
        return 0;
    }

    sprintf(score_text, "Final score: %d", score);
    sprintf(time_text, "Time elapsed: %.2lf", time_elapsed);

    clearDisplay(display);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_text(
        size_lg,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        DISPLAY_HEIGHT/3,
        ALLEGRO_ALIGN_CENTRE,
        title_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD,
        ALLEGRO_ALIGN_CENTRE,
        score_text
    );

    al_draw_text(
        size_md,
        al_map_rgb(255, 255, 255),
        (DISPLAY_WIDTH/2.0),
        (DISPLAY_HEIGHT/3.0) + FONT_SIZE_LG + FONT_SIZE_MD + FONT_SIZE_LG,
        ALLEGRO_ALIGN_CENTRE,
        time_text
    );

    al_flip_display();

    al_rest(5);

    loginfo("gameFinishedMenu finish");

    return 1;
}
