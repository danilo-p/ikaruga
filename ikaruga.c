#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const FPS            = 50;
const DISPLAY_WIDTH  = 500;
const DISPLAY_HEIGHT = 500;
const SHIP_SIZE      = 30;

struct ship {
    ALLEGRO_BITMAP *bitmap;
    int height;
    int width;
    int y;
    int x;
};

typedef struct ship Ship;

void loginfo(char message[255]);
void logerror(char message[255]);

int initGame(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer,
        ALLEGRO_EVENT_QUEUE *event_queue);

void destroyGame(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer,
    ALLEGRO_EVENT_QUEUE *event_queue);

int initShip(Ship *ship);

void destroyShip(Ship *ship);

int main () {

    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    Ship *ship = (Ship *) malloc(sizeof(Ship));

    if(!initGame(display, timer, event_queue)) {
        printf("FATAL: Failed to init game. Exiting...\n");
        return 0;
    }

    if(!initShip(ship)) {
        printf("FATAL: Failed to init ship. Exiting...\n");
        return 0;
    }

    destroyShip(ship);

    destroyGame(display, timer, event_queue);

    return 0;
}

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

int initGame(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer,
        ALLEGRO_EVENT_QUEUE *event_queue) {

    al_init();

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(!display) {
        logerror("Failed to create display");
        return 0;
    } else { loginfo("display created"); }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        logerror("Failed to create timer");
        al_destroy_display(display);
        return 0;
    } else { loginfo("timer created"); }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        logerror("Failed to create event_queue");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return 0;
    } else { loginfo("event_queue created"); }

    loginfo("Game initialized");

    return 1;
}

void destroyGame(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer,
        ALLEGRO_EVENT_QUEUE *event_queue) {

    if(timer) { al_destroy_timer(timer); }
    else { logerror("No timer to destroy"); }

    if(display) { al_destroy_display(display); }
    else { logerror("No display to destroy"); }

    if(event_queue) { al_destroy_event_queue(event_queue); }
    else { logerror("No event_queue to destroy"); }

    loginfo("Game destroyed");
}

int initShip(Ship *ship) {

    ship->bitmap = NULL;
    ship->bitmap = al_create_bitmap(SHIP_SIZE, SHIP_SIZE);
    if(!ship->bitmap) {
        logerror("Failed to create ship");
        return 0;
    } else { loginfo("ship bitmap created"); }

    ship->height = SHIP_SIZE;
    ship->width = SHIP_SIZE;
    ship->x = 0;
    ship->y = 0;

    loginfo("Ship initialized");

    return 1;
}

void destroyShip(Ship *ship) {
    if(ship->bitmap) { al_destroy_bitmap(ship->bitmap); }
    else { logerror("No ship bitmap to destroy"); }

    loginfo("Ship destroyed");
}
