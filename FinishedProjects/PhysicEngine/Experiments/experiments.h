#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "main_menu.h"
#include "object.h"

extern float free_fall_results[];

void free_fall(object_free_fall *obj, float drop_height, float friction_obj, float g, float m, bool air, float friction_air, float k, float a);
