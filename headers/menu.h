#ifndef MENU_H
#define MENU_H

int mainMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);

int pauseMenu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);

int gameFinishedMenu(ALLEGRO_DISPLAY *display, int score, double time_elapsed);

#endif
