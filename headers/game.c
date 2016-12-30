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

bool initGame() {
    if(!al_init()) {
        logerror("Failed to initialize allegro");
        return false;
    }

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    return true;
}

bool startGame(ALLEGRO_DISPLAY *display) {

    // Create the game timer and the event queue
    ALLEGRO_TIMER *timer = createTimer();
    ALLEGRO_EVENT_QUEUE *event_queue = createEventQueue(display, timer);

    // The ikaruga ship, called hero
    Ship hero;
    // The enemies array
    Ship *enemies = NULL;

    // The bullets array and the aux variable new_bullet
    Bullet *bullets = NULL, new_bullet;

    // The timestamp of the last enemy created, initialized with the
    // configurated offset
    double last_enemy_created = FIRST_ENEMY_OFFSET;
    // Aux variable to control the levels difficulty
    double level_factor;
    // Time playing the game
    double time_elapsed;
    // Store the moment that the game started
    double start_time = al_get_time();

    // Aux variable for quit the game
    bool quit = false;
    // Flag for indicating the hero fire
    bool fire_key = false;

    // Counters
    int i, j;
    int bullets_count = 0;
    int enemies_count = 0;
    int score = 0;
    int level = 1;

    // Store the code of the move key pressed
    int move_key_1 = -1;
    int move_key_2 = -1;

    // Load the default font of the game
    ALLEGRO_FONT *size = al_load_font(FONT_FAMILY, FONT_SIZE_SM, 1);
    if(!size) {
        logerror("Failed to load font");
        return false;
    }

    loginfo("startGame enter");

    // Calculate the spawn position of the hero
    int HERO_SPAWN_X = (DISPLAY_WIDTH/2) - (SHIP_SIZE/2);
    int HERO_SPAWN_Y = DISPLAY_HEIGHT - (SHIP_SIZE * 2);

    // Create the hero
    hero = createShip("hero", HERO_SPAWN_X, HERO_SPAWN_Y, up, alpha);
    if(!checkShip(hero)) {
        logerror("Failed to create hero. Game finished.");
        return false;
    }

    // Game loop
    while(!quit) {
        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        // Handler for the timer event
        if(e.type == ALLEGRO_EVENT_TIMER) {

            // Update the time elapsed
            time_elapsed = e.any.timestamp - start_time;

            // Update the game level according to the time elapsed
            level = ((int) time_elapsed / GAME_LEVEL_INTERVAL) + 1;

            // Calculate the difficulty factor of the level
            level_factor = level * GAME_LEVEL_DIFFICULTY_FACTOR;

            /***** Rendering *****/

            clearDisplay(display, al_map_rgb(0,0,0));

            renderShip(hero, display);

            for(i=0; i<bullets_count; i++)
                renderBullet(bullets[i], display);

            for(i=0; i<enemies_count; i++)
                renderShip(enemies[i], display);

            renderGameDisplay(display, level, score, time_elapsed, size, FONT_SIZE_SM);

            /***** Game action *****/

            // Move the ship with the pressed keys
            moveShip(&hero, move_key_1, SHIP_STEP_SIZE);
            moveShip(&hero, move_key_2, SHIP_STEP_SIZE);

            // Check if the fire key is pressed
            if(fire_key) {
                // Try to fire the ship and catch the result
                new_bullet = fireShip(&hero, SHIP_FIRE_INTERVAL, e);

                // Check if the bullet is valid
                if(checkBullet(new_bullet))
                    bullets_count = pushBullet(new_bullet, &bullets, bullets_count);
            }

            // Check if is time to spawn a new enemy
            if(last_enemy_created + ENEMY_SPAWN_INTERVAL / level_factor < time_elapsed) {
                // Spawn a new enemy
                enemies_count = spawnEnemy(&enemies, enemies_count, time_elapsed);
                last_enemy_created = time_elapsed;
            }

            // Fire all the enemies
            for(i=0; i<enemies_count; i++) {
                new_bullet = fireShip(&enemies[i], ENEMY_FIRE_INTERVAL / level_factor, e);
                if(checkBullet(new_bullet))
                    bullets_count = pushBullet(new_bullet, &bullets, bullets_count);
            }

            /***** Movement *****/

            // Move bullets
            for(i=0; i<bullets_count; i++)
                moveBullet( &(bullets[i]) );

            // Move enemies
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

            // Checking hero's bullets - enemy colisions
            for(i=0; i<enemies_count; i++)
                for(j=0; j<bullets_count; j++)
                    if( enemies[i].target == bullets[j].target &&
                        checkBulletShipColision(bullets[j], enemies[i]) &&
                        strstr(bullets[j].id, "hero")
                    ) {
                        // Remove the enemy and the bullet from the game
                        enemies_count = popShip(enemies[i], &enemies, enemies_count);
                        bullets_count = popBullet(bullets[j], &bullets, bullets_count);

                        // Increase the score
                        score++;

                        // Exit the first loop to avoid accessing invalid
                        // pointers on the next iteration
                        break;
                    }

            // Checking bullet - display colisions
            for(i=0; i<bullets_count; i++)
                if(checkBulletDisplayColision(bullets[i]))
                    bullets_count = popBullet(bullets[i], &bullets, bullets_count);

        }
        else if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(e.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    // If both keys are different from the pressed key
                    if(move_key_1 != e.keyboard.keycode &&
                            move_key_2 != e.keyboard.keycode) {

                        // If the first key is not pressed, give it a value.
                        if(move_key_1 == -1) {
                            move_key_1 = e.keyboard.keycode;
                        }
                        // If the second key is not pressed, give it a value.
                        else if(move_key_2 == -1) {
                            move_key_2 = e.keyboard.keycode;
                        }
                        // If both keys are pressed, discard the second value.
                        else {
                            move_key_2 = e.keyboard.keycode;
                        }
                    }
                break;

                case ALLEGRO_KEY_H:
                    fire_key = true;
                break;

                case ALLEGRO_KEY_G:
                    // Change the hero target
                    if(hero.target == alpha)
                        setShipTarget(&hero, gama);
                    else if(hero.target == gama)
                        setShipTarget(&hero, alpha);
                break;

                case ALLEGRO_KEY_P:
                    // Pause the game and stop the timers
                    al_stop_timer(timer);
                    quit = (pauseMenu(display) == 0);
                    al_start_timer(timer);
                break;
            }
        }
        else if(e.type == ALLEGRO_EVENT_KEY_UP) {
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

    // Game finished. Show the score, best score and the time_elapsed
    gameFinishedMenu(display, score, time_elapsed);

    /* Destroy the game elements */

    destroyShip(&hero);

    for(i = 0; i < enemies_count; i++)
        destroyShip(&(enemies[i]));

    for(i = 0; i < enemies_count; i++)
        destroyBullet(&(bullets[i]));

    free(enemies);
    free(bullets);

    destroyTimer(&timer);
    destroyEventQueue(&event_queue);

    loginfo("startGame finish");

    return true;
}

int spawnEnemy(Ship **array, int length, double timestamp) {

    // Set the rand seed as the current time elapsed
    srand(timestamp*10000);

    // Randomize the target and the x position
    type target = rand() % 2 == 0 ? alpha : gama;
    int x = rand() % (DISPLAY_WIDTH - SHIP_SIZE);
    char id[255] = "";

    // Mount the unique enemy id
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
