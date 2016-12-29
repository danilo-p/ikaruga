#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"

void loginfo(const char *message) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d:%d:%d - INFO: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message
    );
}

void logerror(const char *message) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(stderr, "%d:%d:%d - ERROR: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message
    );
}

ALLEGRO_COLOR getTypeColor(type t) {
    if(t == alpha)
        return al_map_rgb(0,0,255);
    else if(t == gama)
        return al_map_rgb(0,255,0);

    return al_map_rgb(0,0,0);
}

//
ALLEGRO_EVENT_QUEUE * createEventQueue(ALLEGRO_DISPLAY *display,
        ALLEGRO_TIMER *timer) {
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    if(!event_queue) {
        logerror("Failed to create event_queue");
        return NULL;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    return event_queue;
}

bool destroyEventQueue(ALLEGRO_EVENT_QUEUE **event_queue) {
    if(!*event_queue) {
        logerror("No event_queue to destroy");
        return false;
    }

    al_destroy_event_queue(*event_queue);
    return true;
}

ALLEGRO_TIMER * createTimer() {
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    if(!timer) {
        logerror("Failed to create timer");
        return NULL;
    }

    al_start_timer(timer);

    return timer;
}

bool destroyTimer(ALLEGRO_TIMER **timer) {
    if(!*timer) {
        logerror("No timer to destroy");
        return false;
    }

    al_destroy_timer(*timer);
    return true;
}

ALLEGRO_DISPLAY * createDisplay() {
    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    if(!display) {
        logerror("Failed to create display");
        return NULL;
    }

    return display;
}

bool destroyDisplay(ALLEGRO_DISPLAY **display) {
    if(!*display) {
        logerror("No display to destroy");
        return false;
    }

    al_destroy_display(*display);
    return true;
}
