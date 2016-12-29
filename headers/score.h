#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SCORE_H
#define SCORE_H

// Read the file that store the best score and return it
int getBestScore();

// Write the given score on the file
bool setBestScore(int score);

#endif
