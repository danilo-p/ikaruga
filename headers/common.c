#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

#include "common.h"

void loginfo(const char *message) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d:%d:%d - INFO: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

void logerror(const char *message) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(stderr, "%d:%d:%d - ERROR: %s\n",
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        message);
}

ALLEGRO_COLOR getTypeColor(type t) {
    if(t == alpha)
        return al_map_rgb(255,0,0);
    else if(t == gama)
        return al_map_rgb(0,255,0);

    return al_map_rgb(0,0,0);
}
