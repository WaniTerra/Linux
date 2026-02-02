#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "main_menu.h"
#include "object.h"

void free_fall(float drop_height, float friction_obj, float g, float m)
{
    // Users Choice
    drop_height = 0;
    friction_obj = 0;
    g = 0;
    m = 0;

    // Findeable
    int time_second = 0;
    float speed = 0;
    float road = 0;
    float v_last = 0;

    // Pinned
    float v_first = 0;

    



}