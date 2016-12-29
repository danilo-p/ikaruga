#include "headers/common.h"
#include "headers/game.h"
#include "headers/display.h"
#include "headers/menu.h"

#include <allegro5/allegro.h>

int main () {

    ALLEGRO_DISPLAY *display = NULL;
    bool quit = false;

    if(!initGame()) {
        logerror("[FATAL] Failed to init game. Exiting...\n");
        return 0;
    }

    display = createDisplay();
    if(!display) {
        logerror("[FATAL] Failed to create display. Exiting...\n");
        return 0;
    }

    while(!quit) {
        switch (mainMenu(display)) {
            case 1:
                startGame(display);
            break;
            case 0:
                quit = true;
            break;
        }
    }

    destroyDisplay(&display);

    return 0;
}
