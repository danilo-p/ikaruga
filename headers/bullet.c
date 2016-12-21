#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"
#include "bullet.h"
#include "element.h"
#include "ship.h"

Bullet createBullet(const Ship owner) {
    // loginfo("createBullet enter");

    // printShip(owner);

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

    if(!checkBullet(bullet)) {
        logerror("Failed to create bullet");
    }

    // printBullet(bullet);

    // loginfo("createBullet finish");
    return bullet;
}

bool checkBullet(const Bullet bullet) {
    return checkElement(bullet.capsule) &&
        bullet.id != NULL && strlen(bullet.id) > 0;
}

void renderBullet(const Bullet bullet, ALLEGRO_DISPLAY *display) {
    // loginfo("renderBullet enter");

    renderElement(bullet.capsule, display);

    // loginfo("renderBullet finish");
}

bool destroyBullet(Bullet *bullet) {
    // loginfo("destroyBullet enter");

    if(!destroyElement(bullet->capsule)) {
        logerror("Failed to destroy bullet capsule");
        return false;
    }

    // loginfo("destroyBullet finish");
    return true;
}

void moveBullet(Bullet *bullet) {
    // loginfo("moveBullet enter");
    moveElement( &(bullet->capsule), bullet->course, BULLET_STEP_SIZE);
    // loginfo("moveBullet finish");
}

Bullet fireShip(Ship *ship, double interval, ALLEGRO_EVENT e) {
    // loginfo("fireShip enter");

    Bullet bullet = (Bullet) {
        .course = 0,
        .id = ""
    };

    // Check fire ratio
    if(ship->last_bullet_fired + interval > e.any.timestamp) {
        // Return empty bullet
        return bullet;
    }

    // Bullet ratio ok. Create the bullet.

    bullet = createBullet(*ship);

    if(checkBullet(bullet)) {
        ship->bullet_count++;
        ship->last_bullet_fired = e.any.timestamp;
    } else {
        logerror("Failed to create bullet");
    }

    // loginfo("fireShip finish");

    return bullet;
}

bool checkBulletShipColision(const Bullet bullet, const Ship ship) {
    // loginfo("checkBulletShipColision");
    return checkElementsColision(bullet.capsule, ship.shape);
}

bool checkBulletDisplayColision(const Bullet bullet) {
    // loginfo("checkBulletDisplayColision");
    return checkElementDisplayColision(bullet.capsule);
}

int pushBullet(const Bullet bullet, Bullet **array, int length) {
    // loginfo("pushBullet enter");

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

    // loginfo("pushBullet finish");

    return length;
}

int popBullet(const Bullet bullet, Bullet **array, int length) {
    // loginfo("popBullet enter");

    int i, j;

    // printf("\n\n\narray[%d]: \n\n", length);
    //
    // printBulletArray(*array, length);

    // loginfo("Trying to find bullet");

    for(i=0; i<length; i++) {
        if(!strcmp( (*array)[i].id , bullet.id )) {

            // loginfo("Bullet found");

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

    // printf("\n\n\nupdated array[%d]: \n\n", length);

    // printBulletArray(*array, length);

    // loginfo("popBullet finish");

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
    for(i=0; i<length; i++) {printBullet(array[i]); }
}
