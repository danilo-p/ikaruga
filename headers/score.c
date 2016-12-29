#include <stdio.h>
#include <stdlib.h>

#include "score.h"
#include "config.h"
#include "common.h"

int getBestScore() {
    char buffer[255];
    FILE *file = fopen(SCORE_FILE, "r");

    if(!file) {
        logerror("Failed to open score file");
        return -1;
    }

    if(!fgets(buffer, 255, file)) {
        fclose(file);
        logerror("Failed to read score file");
        return -1;
    }

    fclose(file);

    return atoi(buffer);
}

bool setBestScore(int score) {
    FILE *file = fopen(SCORE_FILE, "w");

    if(!file) {
        logerror("Failed to open score file");
        return false;
    }

    char score_text[255];

    sprintf(score_text, "%d", score);

    fputs(score_text, file);

    fclose(file);

    return true;
}
