#include <allegro5/allegro.h>

#include "common.h"

#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR color;
    int height;
    int width;
    int y;
    int x;
} Element;

Element createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color);

bool destroyElement(Element element);

bool checkElement(const Element element);

void renderElement(Element element, ALLEGRO_DISPLAY *display);

void moveElement(Element *element, direction course, int step_size);

bool checkElementDisplayColision(Element element);

bool checkElementsColision(Element element_1, Element element_2);

void printElement(const Element element);

#endif
