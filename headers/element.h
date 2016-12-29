#include <allegro5/allegro.h>

#include "common.h"

#ifndef ELEMENT_H
#define ELEMENT_H

// Element structure
typedef struct {
    ALLEGRO_BITMAP *bitmap; // Alegro bitmap for drawing the element
    ALLEGRO_COLOR color; // Element color
    int height; // Element height
    int width; // Element width
    int y; // Element y position on the map
    int x; // Element x position on the map
} Element;

// Create a element with the given dimentions, positions and color
Element createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color);

// Check the element validity
bool destroyElement(Element element);

// Destroy the given element (destroy the bitmap)
bool checkElement(const Element element);

// Render the element with its proportions and position on the given display
void renderElement(Element element, ALLEGRO_DISPLAY *display);

// Move the element on the given course and step size
void moveElement(Element *element, direction course, int step_size);

// Check the colision between the element and the display
bool checkElementDisplayColision(Element element);

// Check the colision between two elements
bool checkElementsColision(Element element_1, Element element_2);

// Print the element formated info
void printElement(const Element element);

#endif
