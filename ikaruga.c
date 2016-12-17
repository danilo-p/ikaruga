#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

const FPS              = 40;

const DISPLAY_WIDTH    = 500;
const DISPLAY_HEIGHT   = 500;

const SHIP_SIZE        = 30;
const SHIP_STEP_SIZE   = 5;

const BULLET_SIZE      = 5;
const BULLET_STEP_SIZE = 15;

typedef enum game_directions {up=1, down, left, right} direction;

typedef struct element {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR color;
    int height;
    int width;
    int y;
    int x;
} Element;

typedef struct ship {
    char id[255];
    direction course;
    Element *shape;
    int bullet_count;
} Ship;

typedef struct bullet {
    char id[255];
    direction course;
    Ship *owner;
    Element *capsule;
} Bullet;

/*********************
 Util functions
 *********************/
void loginfo(char message[255]);
void logerror(char message[255]);

/*********************
 Game functions
 *********************/
int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);
void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue);
bool startGame(ALLEGRO_DISPLAY *display,
        ALLEGRO_EVENT_QUEUE *event_queue);

void pushBullet(Bullet *bullet, Bullet **array, int array_lenght);
int popBullet(Bullet *bullet, Bullet *array, int array_lenght);

/*********************
 Element functions
 *********************/
Element * createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color);
void renderElement(Element *element, ALLEGRO_DISPLAY *display);
void moveElement(Element *element, direction course, int step_size);
bool destroyElement(Element *element);

/*********************
 Ship functions
 *********************/
Ship * createShip(char id[255], direction course, ALLEGRO_COLOR color);
void renderShip(Ship *ship, ALLEGRO_DISPLAY *display);
void moveShip(Ship *ship, direction course);
Bullet * fireShip(Ship *ship);
bool destroyShip(Ship *ship);

/*********************
 Bullet functions
 *********************/
Bullet * createBullet(Ship *owner);
void renderBullet(Bullet *bullet, ALLEGRO_DISPLAY *display);
void moveBullet(Bullet *bullet);
bool destroyBullet(Bullet *bullet);

/*********************
 MAIN
 *********************/
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

/*********************
 Util functions declaration
 *********************/

void loginfo(char message[255]) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d:%d:%d - INFO: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

void logerror(char message[255]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(stderr, "%d:%d:%d - ERROR: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

/*********************
 Game functions declaration
 *********************/

int initGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {

    if(!al_init()) {
        logerror("Failed to initialize allegro");
        return 0;
    }

    *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(!*display) {
        logerror("Failed to create display");
        return 0;
    }

    *timer = al_create_timer(1.0 / FPS);
    if(!*timer) {
        logerror("Failed to create timer");
        al_destroy_display(*display);
        return 0;
    }

    *event_queue = al_create_event_queue();
    if(!*event_queue) {
        logerror("Failed to create event_queue");
        al_destroy_timer(*timer);
        al_destroy_display(*display);
        return 0;
    }

    al_install_keyboard();
    al_init_primitives_addon();

    al_register_event_source(*event_queue, al_get_display_event_source(*display));
    al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
    al_register_event_source(*event_queue, al_get_keyboard_event_source());

    al_start_timer(*timer);

    loginfo("Game initialized");

    return 1;
}

void destroyGame(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer,
        ALLEGRO_EVENT_QUEUE **event_queue) {

    if(*timer) { al_destroy_timer(*timer); }
    else { logerror("No timer to destroy"); }

    if(*display) { al_destroy_display(*display); }
    else { logerror("No display to destroy"); }

    if(*event_queue) { al_destroy_event_queue(*event_queue); }
    else { logerror("No event_queue to destroy"); }

    loginfo("Game destroyed");
}

bool startGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue) {

    Bullet *bullets, *new_bullet;
    int i, bullets_count=0;
    bool quit = false;

    loginfo("Game started");

    Ship *hero = createShip("hero", up, al_map_rgb(255, 0, 0));
    if(!hero) {
        logerror("Failed to create hero. Game finished.\n");
        return false;
    }

    int key_pressed = 0;

    while(!quit) {

        ALLEGRO_COLOR display_color = al_map_rgb(255, 255, 255);
        al_set_target_bitmap(al_get_backbuffer(display));
        al_clear_to_color(display_color);

        renderShip(hero, display);

        for(i=0; i<bullets_count; i++) {
            renderBullet(&bullets[i], display);
        }

        ALLEGRO_EVENT e;
        al_wait_for_event(event_queue, &e);

        if(e.type == ALLEGRO_EVENT_KEY_DOWN) {
            if(key_pressed != e.keyboard.keycode) {
                key_pressed = e.keyboard.keycode;
            }
        } else if(e.type == ALLEGRO_EVENT_KEY_UP) {
            if(key_pressed == e.keyboard.keycode) {
                key_pressed = 0;
            }
        }

        switch(key_pressed) {
            case ALLEGRO_KEY_W:
                if(hero->shape->y > 0)
                    moveShip(hero, up);
            break;

            case ALLEGRO_KEY_S:
                if(hero->shape->y < DISPLAY_HEIGHT - SHIP_SIZE)
                    moveShip(hero, down);
            break;

            case ALLEGRO_KEY_A:
                if(hero->shape->x > 0)
                    moveShip(hero, left);
            break;

            case ALLEGRO_KEY_D:
                if(hero->shape->x < DISPLAY_WIDTH - SHIP_SIZE)
                    moveShip(hero, right);
            break;

            case ALLEGRO_KEY_ENTER:
                quit = true;
            break;
        }

        if(e.type == ALLEGRO_EVENT_KEY_DOWN &&
            e.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            new_bullet = fireShip(hero);
            if(!new_bullet) {
                logerror("Failed to fire ship");
            } else {
                pushBullet(new_bullet, &bullets, bullets_count);
                bullets_count++;
            }
        }

        for(i=0; i<bullets_count; i++) {
            char message[255];
            moveBullet(&bullets[i]);
        }

    }

    if(!destroyShip(hero)) {
        logerror("Failed to destroy ship. Game finished");
        return false;
    }

    loginfo("Game finished");
    return true;
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

/*********************
 Element functions
 *********************/
Element * createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color) {

    Element *element = (Element *) malloc(sizeof(Element));

    element->bitmap = al_create_bitmap(width, height);
    if(!element->bitmap) {
        logerror("Failed to create element bitmap");
        return NULL;
    }

    element->color = color;

    element->height = height;
    element->width = width;
    element->x = x;
    element->y = y;

    return element;
}

void renderElement(Element *element, ALLEGRO_DISPLAY *display) {

    al_set_target_bitmap(element->bitmap);
    al_clear_to_color(element->color);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(element->bitmap, element->x, element->y, 0);

    al_flip_display();

    al_set_target_bitmap(al_get_backbuffer(display));
}

void moveElement(Element *element, direction course, int step_size) {
    switch (course) {
        case up:
            element->y -= step_size;
        break;
        case down:
            element->y += step_size;
        break;
        case left:
            element->x -= step_size;
        break;
        case right:
            element->x += step_size;
        break;
    }
}

bool destroyElement(Element *element) {

    if(!element->bitmap) {
        logerror("No element bitmap to destroy");
        return false;
    }

    al_destroy_bitmap(element->bitmap);

    loginfo("Element destroyed");

    return true;
}

/*********************
 Ship functions declaration
 *********************/

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
    moveElement(ship->shape, course, BULLET_STEP_SIZE);
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

/*********************
 Bullet functions declaration
 *********************/
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

    loginfo("Bullet created");

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

    loginfo("Ship fired");

    return bullet;
}
