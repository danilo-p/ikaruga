#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"
#include "bullet.h"
#include "element.h"
#include "ship.h"

Bullet createBullet(const Ship owner) {
    Bullet bullet = (Bullet) {
        .course = 0,
        .id = ""
    };

    sprintf(bullet.id, "bullet_%d_%s", owner.bullet_count, owner.id);
    bullet.course = owner.course;
    bullet.target = owner.target;

    bullet.capsule = createElement(
        BULLET_SIZE,
        BULLET_SIZE,
        (owner.shape.x) + (owner.shape.width/2) - (BULLET_SIZE/2),
        owner.shape.y,
        owner.shape.color
    );

    if(!checkBullet(bullet))
        logerror("Failed to create bullet");

    return bullet;
}

bool checkBullet(const Bullet bullet) {

    return checkElement(bullet.capsule) &&
        bullet.id != NULL && strlen(bullet.id) > 0;
}

void renderBullet(const Bullet bullet, ALLEGRO_DISPLAY *display) {
    renderElement(bullet.capsule, display);
}

bool destroyBullet(Bullet *bullet) {
    if(!destroyElement(bullet->capsule)) {
        logerror("Failed to destroy bullet capsule");
        return false;
    }

    return true;
}

void moveBullet(Bullet *bullet) {
    moveElement( &(bullet->capsule), bullet->course, BULLET_STEP_SIZE);
}

Bullet fireShip(Ship *ship, double interval, ALLEGRO_EVENT e) {
    Bullet bullet = (Bullet) {
        .course = 0,
        .id = ""
    };

    // Check the ship shot cadency
    if(ship->last_bullet_fired + interval > e.any.timestamp) {
        // Return empty bullet if the ship is trying to shoot too fast
        return bullet;
    }

    bullet = createBullet(*ship);

    if(checkBullet(bullet)) {
        // Iterate the ship bullet counter and register the last time that the
        // ship fired
        ship->bullet_count++;
        ship->last_bullet_fired = e.any.timestamp;
    } else {
        logerror("Failed to create bullet");
    }

    return bullet;
}

bool checkBulletShipColision(const Bullet bullet, const Ship ship) {
    return checkElementsColision(bullet.capsule, ship.shape);
}

bool checkBulletDisplayColision(const Bullet bullet) {
    return checkElementDisplayColision(bullet.capsule);
}

int pushBullet(const Bullet bullet, Bullet **array, int length) {
    if(!length)
        *array = malloc(sizeof(Bullet));
    else
        *array = realloc(*array, (length+1) * sizeof(Bullet));

    if(!*array) {
        logerror("Failed to push bullet");
        return length;
    }

    (*array)[length] = bullet;

    length++;

    return length;
}

int popBullet(const Bullet bullet, Bullet **array, int length) {
    int i, j;

    for(i=0; i<length; i++) {
        if(!strcmp( (*array)[i].id , bullet.id )) {
            destroyBullet( &((*array)[i]) );

            length--;

            for(j=i; j<length; j++)
                (*array)[j] = (*array)[j+1];

            if(length > 0){
                *array = realloc(*array, (length) * sizeof(Bullet));
            } else {
                free(*array);
                *array = NULL;
            }

            break;
        }
    }

    return length;
}

void printBullet(const Bullet bullet) {
    printf("\nBullet %s\ncourse: %d\n",
        bullet.id,
        bullet.course
    );

    printElement(bullet.capsule);
}

void printBulletArray(const Bullet *array, int length) {
    int i=0;

    for(i=0; i<length; i++)
        printBullet(array[i]);
}
