#include <stdio.h>
#include <allegro5/allegro.h>

#include "config.h"
#include "common.h"
#include "element.h"
#include "ship.h"
#include "bullet.h"

Bullet * createBullet(Ship *owner) {

    Bullet *bullet = (Bullet *) malloc(sizeof(Bullet));

    bullet->capsule = createElement(
        BULLET_SIZE,
        BULLET_SIZE,
        owner->shape->x + owner->shape->width/2,
        owner->shape->y,
        owner->shape->color
    );

    if(!bullet->capsule) {
        logerror("Failed to create bullet capsule");
        return NULL;
    }

    sprintf(bullet->id, "bullet_%d_%s", owner->bullet_count, owner->id);
    bullet->course = owner->course;
    bullet->owner = owner;

    return bullet;
}

void renderBullet(Bullet *bullet, ALLEGRO_DISPLAY *display) {
    renderElement(bullet->capsule, display);
}

bool destroyBullet(Bullet *bullet) {

    if(!destroyElement(bullet->capsule)) {
        logerror("Failed to destroy bullet capsule");
        return false;
    }

    free(bullet);

    loginfo("Bullet destroyed");
    return true;
}

void moveBullet(Bullet *bullet) {
    moveElement(bullet->capsule, bullet->course, BULLET_STEP_SIZE);
}

Bullet * fireShip(Ship *ship) {
    Bullet *bullet = createBullet(ship);
    if(!bullet) {
        logerror("Failed to create bullet");
        return NULL;
    }

    ship->bullet_count++;

    return bullet;
}


void pushBullet(Bullet *bullet, Bullet **array, int array_lenght) {

    Bullet * new_array = NULL;

    if(array_lenght == 0){
        new_array = (Bullet *) malloc(sizeof(Bullet));
    } else {
        new_array = (Bullet *) realloc(*array, (array_lenght+1) * sizeof(Bullet));
    }

    if(new_array) {
        new_array[array_lenght] = *bullet;
        Bullet new_bullet = new_array[array_lenght];
        *array = new_array;
    } else {
        logerror("Failed to push bullet");
    }
}

int popBullet(Bullet *bullet, Bullet *array, int array_lenght) {

    Bullet *new_array;
    int i, new_array_length = 0;

    for(i=0; i<array_lenght; i++) {
        if(array[i].id == bullet->id){
            destroyBullet(&array[i]);
        } else {
            pushBullet(&array[i], &new_array, new_array_length);
            new_array_length++;
        }
    }

    destroyBullet(bullet);
    free(array);
    array = new_array;

    return new_array_length;
}
