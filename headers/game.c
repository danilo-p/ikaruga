#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"

#include "bullet.h"
#include "ship.h"

#include "game.h"

int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {

    if(!al_init()) {
        logerror("Failed to initialize allegro");
        return 0;
    }

    *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(!*display) {
        logerror("Failed to create display");
        return 0;
    }

    *timer = al_create_timer(1.0 / FPS);
    if(!*timer) {
        logerror("Failed to create timer");
        al_destroy_display(*display);
        return 0;
    }

    *event_queue = al_create_event_queue();
    if(!*event_queue) {
        logerror("Failed to create event_queue");
        al_destroy_timer(*timer);
        al_destroy_display(*display);
        return 0;
    }

    al_install_keyboard();
    al_init_primitives_addon();

    al_register_event_source(*event_queue, al_get_display_event_source(*display));
    al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
    al_register_event_source(*event_queue, al_get_keyboard_event_source());

    al_start_timer(*timer);

    loginfo("Game initialized");

    return 1;
}

void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {

    if(*timer) { al_destroy_timer(*timer); }
    else { logerror("No timer to destroy"); }

    if(*display) { al_destroy_display(*display); }
    else { logerror("No display to destroy"); }

    if(*event_queue) { al_destroy_event_queue(*event_queue); }
    else { logerror("No event_queue to destroy"); }

    loginfo("Game destroyed");
}

bool startGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue) {

    Bullet *bullets, *new_bullet;
    int i, bullets_count=0;
    bool quit = false;

    loginfo("Game started");

    Ship *hero = createShip("hero", up, al_map_rgb(255, 0, 0));
    if(!hero) {
        logerror("Failed to create hero. Game finished.\n");
        return false;
    }

    int key_pressed_1=0;
    int key_pressed_2=0;

    while(!quit) {

        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    if(hero->shape->y > 0)
                        moveShip(hero, up);
                break;

                case ALLEGRO_KEY_S:
                    if(hero->shape->y < DISPLAY_HEIGHT - SHIP_SIZE)
                        moveShip(hero, down);
                break;

                case ALLEGRO_KEY_A:
                    if(hero->shape->x > 0)
                        moveShip(hero, left);
                break;

                case ALLEGRO_KEY_D:
                    if(hero->shape->x < DISPLAY_WIDTH - SHIP_SIZE)
                        moveShip(hero, right);
                break;

                case ALLEGRO_KEY_SPACE:
                    new_bullet = fireShip(hero);
                    if(!new_bullet) {
                        logerror("Failed to fire ship");
                    } else {
                        pushBullet(new_bullet, &bullets, bullets_count);
                        bullets_count++;
                    }
                break;

                case ALLEGRO_KEY_ENTER:
                    quit = true;
                break;
            }
        } else if(e.type == ALLEGRO_EVENT_TIMER) {

            ALLEGRO_COLOR display_color = al_map_rgb(255, 255, 255);
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(display_color);

            renderShip(hero, display);

            for(i=0; i<bullets_count; i++) {
                renderBullet(&bullets[i], display);
            }

            for(i=0; i<bullets_count; i++) {
                char message[255];
                moveBullet(&bullets[i]);
            }
        }
    }

    if(!destroyShip(hero)) {
        logerror("Failed to destroy ship. Game finished");
        return false;
    }

    loginfo("Game finished");
    return true;
}
