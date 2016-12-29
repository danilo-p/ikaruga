#include "headers/common.h"
#include "headers/game.h"
#include "headers/display.h"
#include "headers/menu.h"

#include <allegro5/allegro.h>

int main () {

    ALLEGRO_DISPLAY *display         = NULL;
    // ALLEGRO_TIMER *timer             = NULL;
    // ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    // if(!initGame(&display, &timer, &event_queue)) {
    if(!initGame()) {
        logerror("[FATAL] Failed to init game. Exiting...\n");
        return 0;
    }

    display = createDisplay();

    if(!display) {
        logerror("[FATAL] Failed to create display. Exiting...\n");
        return 0;
    }

    bool quit = false;

    while(!quit) {
        // switch (mainMenu(display, event_queue)) {
        switch (mainMenu(display)) {
            case 1:
                // startGame(display, event_queue);
                startGame(display);
            break;
            case 0:
                quit = true;
            break;
        }
    }

    destroyDisplay(&display);

    // destroyGame(&display, &timer, &event_queue);

    return 0;
}
