#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

const FPS            = 40;
const DISPLAY_WIDTH  = 500;
const DISPLAY_HEIGHT = 500;
const SHIP_SIZE      = 30;
const SHIP_STEP_SIZE = 5;

struct ship {
    ALLEGRO_BITMAP *bitmap;
    int height;
    int width;
    int y;
    int x;
};
typedef struct ship Ship;

/*********************
 Util functions
 *********************/
void loginfo(char message[255]);
void logerror(char message[255]);

/*********************
 Game functions
 *********************/
int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);
void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);
void startGame(Ship *ship, ALLEGRO_DISPLAY *display,
        ALLEGRO_EVENT_QUEUE *event_queue);

/*********************
 Ship functions
 *********************/
Ship * createShip();
void renderShip(Ship *ship, ALLEGRO_DISPLAY *display);
void destroyShip(Ship *ship);

/*********************
 MAIN
 *********************/
int main () {

    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if(!initGame(&display, &timer, &event_queue)) {
        logerror("[FATAL] Failed to init game. Exiting...\n");
        return 0;
    }

    Ship *ship = createShip();
    if(!ship) {
        logerror("[FATAL] Failed to create ship. Exiting...\n");
        return 0;
    }

    startGame(ship, display, event_queue);

    destroyGame(&display, &timer, &event_queue);

    return 0;
}

/*********************
 Util functions declaration
 *********************/

void loginfo(char message[255]) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d:%d:%d - INFO: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

void logerror(char message[255]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(stderr, "%d:%d:%d - ERROR: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

/*********************
 Game functions declaration
 *********************/

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

    al_set_target_bitmap(al_get_backbuffer(*display));
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();

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

void startGame(Ship *ship, ALLEGRO_DISPLAY *display,
        ALLEGRO_EVENT_QUEUE *event_queue) {

    loginfo("Game started");

    int key_pressed = 0;

    bool quit = false;
    while(!quit) {

        renderShip(ship, display);

        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            if(key_pressed != e.keyboard.keycode) {
                key_pressed = e.keyboard.keycode;
            }
        } else if(e.type == ALLEGRO_EVENT_KEY_UP) {
            if(key_pressed == e.keyboard.keycode) {
                key_pressed = 0;
            }
        }

        switch(key_pressed) {
            case ALLEGRO_KEY_W:
                if(ship->y > 0)
                    ship->y -= SHIP_STEP_SIZE;
            break;

            case ALLEGRO_KEY_S:
                if(ship->y < DISPLAY_HEIGHT - SHIP_SIZE)
                    ship->y += SHIP_STEP_SIZE;
            break;

            case ALLEGRO_KEY_A:
                if(ship->x > 0)
                    ship->x -= SHIP_STEP_SIZE;
            break;

            case ALLEGRO_KEY_D:
                if(ship->x < DISPLAY_WIDTH - SHIP_SIZE)
                    ship->x += SHIP_STEP_SIZE;
            break;

            case ALLEGRO_KEY_ENTER:
                quit = true;
            break;
        }
    }

    loginfo("Game finished");

    destroyShip(ship);
}

/*********************
 Ship functions declaration
 *********************/

Ship * createShip() {

    Ship *ship = (Ship *) malloc(sizeof(Ship));

    ship->bitmap = al_create_bitmap(SHIP_SIZE, SHIP_SIZE);
    if(!ship->bitmap) {
        logerror("Failed to create ship");
        return NULL;
    }

    ship->height = SHIP_SIZE;
    ship->width = SHIP_SIZE;
    ship->x = 0;
    ship->y = 0;

    loginfo("Ship initialized");

    return ship;
}

void renderShip(Ship *ship, ALLEGRO_DISPLAY *display) {

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(255, 255, 255));


    al_set_target_bitmap(ship->bitmap);
    al_clear_to_color(al_map_rgb(255, 0, 0));

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(ship->bitmap, ship->x, ship->y, 0);

    al_flip_display();

    al_set_target_bitmap(al_get_backbuffer(display));
}

void destroyShip(Ship *ship) {
    if(ship->bitmap) { al_destroy_bitmap(ship->bitmap); }
    else { logerror("No ship bitmap to destroy"); }

    loginfo("Ship destroyed");
}
