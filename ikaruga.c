#include "headers/common.h"
#include "headers/game.h"

#include <allegro5/allegro.h>

int main () {

    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if(!initGame(&display, &timer, &event_queue)) {
        logerror("[FATAL] Failed to init game. Exiting...\n");
        return 0;
    }

    startGame(display, event_queue);

    destroyGame(&display, &timer, &event_queue);

    return 0;
}
