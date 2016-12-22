#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"
#include "config.h"
#include "common.h"
#include "display.h"
#include "game.h"
#include "ship.h"
#include "menu.h"

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
    al_init_font_addon();
    al_init_ttf_addon();

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

    Ship hero, *enemies = NULL;
    Bullet *bullets = NULL, new_bullet;
    int i, j, bullets_count = 0, enemies_count = 0, score = 0, level = 1;
    double last_enemy_created = FIRST_ENEMY_OFFSET, level_factor, time_elapsed;
    bool quit = false;

    int move_key_1 = -1, move_key_2 = -1;
    bool fire_key = false;

    ALLEGRO_FONT *size = NULL;

    size = al_load_font(FONT_FAMILY, FONT_SIZE_SM, 1);
    if(!size) {
        logerror("Failed to load font");
        return false;
    }

    loginfo("startGame enter");

    int HERO_SPAWN_X = (DISPLAY_WIDTH/2) - (SHIP_SIZE/2);
    int HERO_SPAWN_Y = DISPLAY_HEIGHT - (SHIP_SIZE * 2);

    hero = createShip("hero", HERO_SPAWN_X, HERO_SPAWN_Y, up, alpha);

    if(!checkShip(hero)) {
        logerror("Failed to create hero. Game finished.");
        return false;
    }

    while(!quit) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_TIMER) {

            time_elapsed = e.any.timestamp;
            level = ((int) e.any.timestamp / GAME_LEVEL_INTERVAL) + 1;

            level_factor = level / GAME_LEVEL_DIFFICULTY_FACTOR;

            /***** Rendering *****/

            clearDisplay(display);

            renderShip(hero, display);

            for(i=0; i<bullets_count; i++)
                renderBullet(bullets[i], display);

            for(i=0; i<enemies_count; i++)
                renderShip(enemies[i], display);

            renderGameDisplay(display, level, score, e.any.timestamp, size, FONT_SIZE_SM);

            /***** Game action *****/

            // Hero actions
            moveShip(&hero, move_key_1, SHIP_STEP_SIZE);
            moveShip(&hero, move_key_2, SHIP_STEP_SIZE);
            if(fire_key) {
                new_bullet = fireShip(&hero, SHIP_FIRE_INTERVAL, e);
                if(checkBullet(new_bullet))
                    bullets_count = pushBullet(new_bullet, &bullets, bullets_count);
            }

            // Spawn enemies
            if(last_enemy_created + ENEMY_SPAWN_INTERVAL / level_factor < e.any.timestamp) {
                enemies_count = spawnEnemy(&enemies, enemies_count, e.any.timestamp);
                last_enemy_created = e.any.timestamp;
            }

            for(i=0; i<enemies_count; i++) {
                new_bullet = fireShip(&enemies[i], ENEMY_FIRE_INTERVAL / level_factor, e);
                if(checkBullet(new_bullet))
                    bullets_count = pushBullet(new_bullet, &bullets, bullets_count);
            }

            /***** Movement *****/

            // Moving bullets
            for(i=0; i<bullets_count; i++)
                moveBullet( &(bullets[i]) );

            // Moving enemies
            for(i=0; i<enemies_count; i++)
                moveEnemy(hero, &(enemies[i]) );

            /***** Colisions check *****/

            // Checking hero - enemy colisions
            for(i=0; i<enemies_count; i++)
                if(checkShipsColision(hero, enemies[i])) quit = true;

            // Checking enemy bullets - hero colisions
            for(i=0; i<bullets_count; i++)
                if( hero.target == bullets[i].target &&
                    checkBulletShipColision(bullets[i], hero) &&
                    strstr(bullets[i].id, "enemy")
                ) quit = true;

            // Checking hero bullets - enemy colisions
            for(i=0; i<enemies_count; i++)
                for(j=0; j<bullets_count; j++)
                    if( enemies[i].target == bullets[j].target &&
                        checkBulletShipColision(bullets[j], enemies[i]) &&
                        strstr(bullets[j].id, "hero")
                    ) {
                        enemies_count = popShip(enemies[i], &enemies, enemies_count);
                        bullets_count = popBullet(bullets[j], &bullets, bullets_count);
                        score++;
                        // Exit the first loop to avoid accessing invalid
                        // pointers on the next iteration
                        break;
                    }

            // Checking bullet - display colisions
            for(i=0; i<bullets_count; i++)
                if(checkBulletDisplayColision(bullets[i]))
                    bullets_count = popBullet(bullets[i], &bullets, bullets_count);

        } else if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    // If both keys are different from the pressed key
                    if(move_key_1 != e.keyboard.keycode &&
                            move_key_2 != e.keyboard.keycode) {

                        // If the first key is not pressed. Give it a value.
                        if(move_key_1 == -1) {
                            move_key_1 = e.keyboard.keycode;
                        }
                        // If the second key is not pressed. Give it a value.
                        else if(move_key_2 == -1) {
                            move_key_2 = e.keyboard.keycode;
                        }
                        // If both keys are pressed. Discard the second value.
                        else {
                            move_key_2 = e.keyboard.keycode;
                        }
                    }
                break;

                case ALLEGRO_KEY_H:
                    fire_key = true;
                break;

                case ALLEGRO_KEY_G:
                    if(hero.target == alpha)
                        setShipTarget(&hero, gama);
                    else if(hero.target == gama)
                        setShipTarget(&hero, alpha);
                break;

                case ALLEGRO_KEY_P:
                    quit = (pauseMenu(display, event_queue) == 0);
                break;
            }
        } else if(e.type == ALLEGRO_EVENT_KEY_UP) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    if(move_key_1 == e.keyboard.keycode)
                        move_key_1 = -1;

                    if(move_key_2 == e.keyboard.keycode)
                        move_key_2 = -1;

                break;

                case ALLEGRO_KEY_H:
                    fire_key = false;
                break;
            }
        }
    }

    gameFinishedMenu(display, score, time_elapsed);

    if(!destroyShip(&hero)) {
        logerror("Failed to destroy ship. Game finished");
        return false;
    }

    loginfo("startGame finish");
    return true;
}

int spawnEnemy(Ship **array, int length, double timestamp) {

    srand(timestamp*10000);

    type target = rand() % 2 == 0 ? alpha : gama;
    int x = rand() % (DISPLAY_WIDTH - SHIP_SIZE);
    char id[255] = "";

    sprintf(id, "enemy_%.0lf", timestamp);

    Ship enemy = createShip(id, x, 0, down, target);

    if(!checkShip(enemy)) {
        return length;
    }

    return pushShip(enemy, array, length);
}

void moveEnemy(const Ship hero, Ship *enemy) {

    if(enemy->shape.x < hero.shape.x)
        moveShip(enemy, right, ENEMY_STEP_SIZE);
    else
        moveShip(enemy, left, ENEMY_STEP_SIZE);

    if(enemy->shape.y < hero.shape.y)
        moveShip(enemy, down, ENEMY_STEP_SIZE);
    else
        moveShip(enemy, up, ENEMY_STEP_SIZE);

}
