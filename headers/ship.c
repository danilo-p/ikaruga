#include <allegro5/allegro.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "element.h"
#include "ship.h"

Ship createShip(char id[255], int x, int y, direction course, ALLEGRO_COLOR color) {
    loginfo("createShip enter");

    Ship ship = (Ship) {
        .course = course,
        .bullet_count = 0,
        .last_bullet_fired = 0,
        .id = "",
    };

    ship.shape = createElement(SHIP_SIZE, SHIP_SIZE, x, y, color);

    strcpy(ship.id, id);

    if(!checkShip(ship)) {
        logerror("Failed to create ship shape");
    }

    loginfo("createShip finish");

    return ship;
}

bool checkShip(const Ship ship) {
    return checkElement(ship.shape) && ship.id != NULL && strlen(ship.id) > 0;
}

void renderShip(const Ship ship, ALLEGRO_DISPLAY *display) {
    loginfo("renderShip enter");

    renderElement(ship.shape, display);

    loginfo("renderShip finish");
}

void moveShip(Ship *ship, direction course) {
    loginfo("moveShip enter");

    moveElement( &(ship->shape), course, SHIP_STEP_SIZE);

    loginfo("moveShip finish");
}

bool destroyShip(Ship *ship) {
    loginfo("destroyShip enter");

    if(!destroyElement(ship->shape)) {
        logerror("Failed to destroy ship shape");
        return false;
    }

    loginfo("destroyShip finish");
    return true;
}

bool checkShipsColision(const Ship ship_1, const Ship ship_2) {
    loginfo("checkShipsColision");
    return checkElementsColision(ship_1.shape, ship_2.shape);
}

bool checkShipDisplayColision(const Ship ship) {
    loginfo("checkShipDisplayColision");
    return checkElementDisplayColision(ship.shape);
}

void printShip(const Ship ship) {
    printf("\nShip %s\ncourse: %d\nbullet_count: %d\n",
        ship.id,
        ship.course,
        ship.bullet_count
    );
    printElement(ship.shape);
}

void printShipArray(const Ship *array, int length) {
    int i=0;
    for(i=0; i<length; i++) {printShip(array[i]); }
}

int pushShip(const Ship ship, Ship **array, int length) {
    loginfo("pushShip enter");

    if(!length)
        *array = malloc(sizeof(Ship));
    else
        *array = realloc(*array, (length+1) * sizeof(Ship));


    if(!*array) {
        logerror("Failed to push ship");
        return length;
    }

    (*array)[length] = ship;

    length++;

    loginfo("pushShip finish");

    return length;
}

int popShip(const Ship ship, Ship **array, int length) {
    loginfo("popShip enter");

    int i, j;

    printf("\n\n\narray[%d]: \n\n", length);

    printShipArray(*array, length);

    loginfo("Trying to find ship");

    for(i=0; i<length; i++) {
        if(!strcmp( (*array)[i].id , ship.id )) {

            loginfo("Ship found");

            destroyShip( &((*array)[i]) );

            length--;

            for(j=i; j<length; j++)
                (*array)[j] = (*array)[j+1];

            if(length > 0){
                *array = realloc(*array, (length) * sizeof(Ship));
            } else {
                free(*array);
                *array = NULL;
            }

            break;
        }
    }

    printf("\n\n\nupdated array[%d]: \n\n", length);

    printShipArray(*array, length);

    loginfo("popShip finish");

    return length;
}
