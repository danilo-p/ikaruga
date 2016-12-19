#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"
#include "element.h"
#include "ship.h"

Ship * createShip(char id[255], direction course, ALLEGRO_COLOR color) {

    Ship *ship = (Ship *) malloc(sizeof(Ship));

    ship->shape = createElement(SHIP_SIZE, SHIP_SIZE, 0, 0, color);
    if(!ship->shape) {
        logerror("Failed to create ship shape");
        return NULL;
    }

    strcpy(ship->id, id);
    ship->course = course;
    ship->bullet_count=0;

    loginfo("Ship created");

    return ship;
}

void renderShip(Ship *ship, ALLEGRO_DISPLAY *display) {
    renderElement(ship->shape, display);
}

void moveShip(Ship *ship, direction course) {
    moveElement(ship->shape, course, SHIP_STEP_SIZE);
}

bool destroyShip(Ship *ship) {
    if(!destroyElement(ship->shape)) {
        logerror("Failed to destroy ship shape");
        return false;
    }

    free(ship);

    loginfo("Ship destroyed");
    return true;
}
