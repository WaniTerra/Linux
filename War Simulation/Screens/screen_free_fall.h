#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "object.h"
#include "main_menu.h"

void setup_free_fall();
int screen_free_fall();
object_free_fall create_object_temp(int *mx, int *my);
void create_object(int *mx, int *my);
void create_object_move(int *mx, int *my);
