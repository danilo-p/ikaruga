#include <allegro5/allegro.h>

#include "common.h"
#include "element.h"

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
