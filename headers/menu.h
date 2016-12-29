#ifndef MENU_H
#define MENU_H

int mainMenu(ALLEGRO_DISPLAY *display);

int pauseMenu(ALLEGRO_DISPLAY *display);

int gameFinishedMenu(ALLEGRO_DISPLAY *display, int score, double time_elapsed);

#endif
