#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"
#include "bullet.h"
#include "element.h"
#include "ship.h"

Bullet createBullet(Ship *owner) {
    loginfo("createBullet enter");

    printShip(*owner);

    Bullet bullet = (Bullet) {
        .course = 0,
        .owner = NULL,
        .id = ""
    };

    sprintf(bullet.id, "bullet_%d_%s", owner->bullet_count, owner->id);
    bullet.course = owner->course;
    bullet.owner = owner;

    bullet.capsule = createElement(
        BULLET_SIZE,
        BULLET_SIZE,
        owner->shape.x + owner->shape.width/2.0,
        owner->shape.y,
        owner->shape.color
    );

    if(!checkBullet(bullet)) {
        logerror("Failed to create bullet");
    }

    printBullet(bullet);

    loginfo("createBullet finish");
    return bullet;
}

bool checkBullet(const Bullet bullet) {
    return checkElement(bullet.capsule) && bullet.owner != NULL &&
        bullet.id != NULL && strlen(bullet.id) > 0;
}

void renderBullet(const Bullet bullet, ALLEGRO_DISPLAY *display) {
    loginfo("renderBullet enter");

    renderElement(bullet.capsule, display);

    loginfo("renderBullet finish");
}

bool destroyBullet(Bullet *bullet) {
    loginfo("destroyBullet enter");

    if(!destroyElement(bullet->capsule)) {
        logerror("Failed to destroy bullet capsule");
        return false;
    }

    loginfo("destroyBullet finish");
    return true;
}

void moveBullet(Bullet *bullet) {
    loginfo("moveBullet enter");
    moveElement(bullet->capsule, bullet->course, BULLET_STEP_SIZE);
    loginfo("moveBullet finish");
}

Bullet fireShip(Ship *ship) {
    loginfo("fireShip enter");

    Bullet bullet = createBullet(ship);

    if(checkBullet(bullet)) {
        ship->bullet_count++;
    } else {
        logerror("Failed to create bullet");
    }

    loginfo("fireShip finish");

    return bullet;
}

bool checkBulletShipColision(const Bullet bullet, const Ship ship) {
    loginfo("checkBulletShipColision");
    return checkElementsColision(bullet.capsule, ship.shape);
}

bool checkBulletDisplayColision(const Bullet bullet) {
    loginfo("checkBulletDisplayColision");
    return checkElementDisplayColision(bullet.capsule);
}

int pushBullet(const Bullet bullet, Bullet **array, int length) {
    loginfo("pushBullet enter");

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

    loginfo("pushBullet finish");

    return length;
}

int popBullet(const Bullet bullet, Bullet **array, int length) {
    loginfo("popBullet enter");

    int i, j;

    for(i=0; i<length; i++) {
        if(!strcmp( (*array)[i].id , bullet.id )) {
            for(j=i; j<length; j++)
                array[j] = array[j+1];

            length--;

            *array = realloc(*array, (length) * sizeof(Bullet));

            break;
        }
    }

    loginfo("popBullet finish");

    return length;
}

void printBullet(const Bullet bullet) {
    printf("\nBullet %s\ncourse: %d\n",
        bullet.id,
        bullet.course
    );
    printShip( *(bullet.owner) );
    printElement(bullet.capsule);
}

void printBulletArray(const Bullet *array, int length) {
    int i=0;
    for(i=0; i<length; i++) {printBullet(array[i]); }
}
