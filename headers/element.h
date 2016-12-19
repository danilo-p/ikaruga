#include <allegro5/allegro.h>

#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct element {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR color;
    int height;
    int width;
    int y;
    int x;
} Element;

Element * createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color);

void renderElement(Element *element, ALLEGRO_DISPLAY *display);

void moveElement(Element *element, direction course, int step_size);

bool destroyElement(Element *element);

#endif
