#ifndef MENU_H
#define MENU_H

// Show the initial menu of the game and returns the option selected
int mainMenu(ALLEGRO_DISPLAY *display);

// Show the pause menu of the game and returns the option selected
int pauseMenu(ALLEGRO_DISPLAY *display);

// Show the menu of the end of a match with the score, best score and time elapsed
int gameFinishedMenu(ALLEGRO_DISPLAY *display, int score, double time_elapsed);

#endif
