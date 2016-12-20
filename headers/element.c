#include <allegro5/allegro.h>
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "element.h"

Element createElement(int width, int height, int x, int y,
        ALLEGRO_COLOR color) {

    Element element = (Element) {
        .color = color,
        .height = height,
        .width = width,
        .y = y,
        .x = x
    };

    element.bitmap = al_create_bitmap(width, height);

    if(!checkElement(element)) {
        logerror("Failed to create element bitmap");
    }

    return element;
}

bool checkElement(const Element element) {
    return element.bitmap != NULL;
}

bool destroyElement(Element element) {

    if(!element.bitmap) {
        logerror("No element bitmap to destroy");
        return false;
    }

    al_destroy_bitmap(element.bitmap);

    element.bitmap = NULL;

    loginfo("Element destroyed");

    return true;
}

void renderElement(Element element, ALLEGRO_DISPLAY *display) {
    al_set_target_bitmap(element.bitmap);
    al_clear_to_color(element.color);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(element.bitmap, element.x, element.y, 0);
}

void moveElement(Element element, direction course, int step_size) {
    switch (course) {
        case up:
            element.y -= step_size;
        break;
        case down:
            element.y += step_size;
        break;
        case left:
            element.x -= step_size;
        break;
        case right:
            element.x += step_size;
        break;
    }
}

bool checkElementDisplayColision(Element element) {
    return (
        element.y < 0 ||
        element.y > DISPLAY_HEIGHT - element.height ||
        element.x < 0 ||
        element.x > DISPLAY_WIDTH - element.width
    );
}

bool checkElementsColision(Element element_1, Element element_2) {
    return (
        element_2.x > element_1.x &&
        element_2.x < element_1.x + element_1.width &&
        element_2.y > element_1.y &&
        element_2.y < element_1.y + element_1.height
    ) ||
    (
        element_1.x > element_2.x &&
        element_1.x < element_2.x + element_2.width &&
        element_1.y > element_2.y &&
        element_1.y < element_2.y + element_2.height
    );
}

void printElement(const Element element) {
    printf("\nElement %s\nheight: %d\nwidth: %d\nx: %d\ny: %d\n",
        checkElement(element) ? "ok" : "nok",
        element.height,
        element.width,
        element.y,
        element.x
    );
}
