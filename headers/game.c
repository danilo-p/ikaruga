#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "bullet.h"
#include "config.h"
#include "common.h"
#include "display.h"
#include "game.h"
#include "ship.h"

int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {

    loginfo("initGame enter");

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

    loginfo("initGame finish");

    return 1;
}

void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {
    loginfo("destroyGame enter");

    if(*timer) { al_destroy_timer(*timer); }
    else { logerror("No timer to destroy"); }

    if(*display) { al_destroy_display(*display); }
    else { logerror("No display to destroy"); }

    if(*event_queue) { al_destroy_event_queue(*event_queue); }
    else { logerror("No event_queue to destroy"); }

    loginfo("destroyGame finish");
}

bool startGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue) {

    Ship hero;
    Bullet *bullets = NULL, new_bullet;
    int i, bullets_count = 0;
    bool quit = false;

    loginfo("startGame enter");

    hero = createShip("hero", up, al_map_rgb(255, 0, 0));

    if(!checkShip(hero)) {
        logerror("Failed to create hero. Game finished.");
        return false;
    }

    while(!quit) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_TIMER) {

            printf("\n\n");

            loginfo("timer event enter");

            // Rendering the game

            clearDisplay(display);

            renderShip(hero, display);

            printBulletArray(bullets, bullets_count);

            for(i=0; i<bullets_count; i++) {
                renderBullet(bullets[i], display);
            }

            renderDisplay(display);

            // Moving elements

            for(i=0; i<bullets_count; i++) { moveBullet( &(bullets[i]) ); }

            for(i=0; i<bullets_count; i++) {
                printBullet(bullets[i]);

                if(checkBulletDisplayColision(bullets[i]))
                    popBullet(bullets[i], &bullets, bullets_count);
            }

            loginfo("timer event finish");

            printf("\n\n");
        } else if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            printf("\n\n");
            loginfo("key down event enter");

            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    loginfo("ALLEGRO_KEY_W");
                    if(hero.shape.y > 0)
                        moveShip(&hero, up);
                break;

                case ALLEGRO_KEY_S:
                    loginfo("ALLEGRO_KEY_S");
                    if(hero.shape.y < DISPLAY_HEIGHT - SHIP_SIZE)
                        moveShip(&hero, down);
                break;

                case ALLEGRO_KEY_A:
                    loginfo("ALLEGRO_KEY_A");
                    if(hero.shape.x > 0)
                        moveShip(&hero, left);
                break;

                case ALLEGRO_KEY_D:
                    loginfo("ALLEGRO_KEY_D");
                    if(hero.shape.x < DISPLAY_WIDTH - SHIP_SIZE)
                        moveShip(&hero, right);
                break;

                case ALLEGRO_KEY_SPACE:
                    loginfo("ALLEGRO_KEY_SPACE");
                    new_bullet = fireShip(&hero);
                    if(checkBullet(new_bullet)) {
                        bullets_count = pushBullet(new_bullet, &bullets,
                            bullets_count);
                        printBulletArray(bullets, bullets_count);
                    } else {
                        logerror("Failed to fire ship");
                    }
                break;

                case ALLEGRO_KEY_ENTER:
                    loginfo("ALLEGRO_KEY_ENTER");
                    quit = true;
                break;
            }

            loginfo("key down event finish");
            printf("\n\n");

            // getchar();
        }
    }

    if(!destroyShip(&hero)) {
        logerror("Failed to destroy ship. Game finished");
        return false;
    }

    loginfo("startGame finish");
    return true;
}
