#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../main_menu.h"
#include "../object.h"

void free_fall(object_free_fall *obj, float drop_height, float friction_obj, float g, float m, bool air, float friction_air, float k, float a)
{
    // Users Choice
    drop_height = 0;
    friction_obj = 0;
    g = 0;
    m = 0;

    // Pinned
    float v_first = 0;

    if (!air)
    {
        (*obj).results[1] = g * (*obj).results[0];
        (*obj).results[2] = (1 / 2) * g * (*obj).results[0] * (*obj).results[0];
        (*obj).results[3] = sqrt(2 * g * (*obj).results[2]);
    }
    else
    {
        friction_air = k * a * (*obj).results[1];
        (*obj).results[2] = ((*obj).results[1] * (*obj).results[1] / g) * log(cosh((g * (*obj).results[0]) / (*obj).results[1]));

        if ((m * g) <= k * a * (*obj).results[1] * (*obj).results[1])
        {
            (*obj).results[1] = (*obj).results[1] * tanh((g * (*obj).results[0]) / (*obj).results[1]);
        }
        else
        {
            (*obj).results[1] = (*obj).results[1] * tanh((g * (*obj).results[0]) / (*obj).results[1]);
        }
    }
}