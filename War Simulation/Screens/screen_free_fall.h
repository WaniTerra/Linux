#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "object.h"
#include "main_menu.h"

#define OBJ_FF_HEIGHT 50
#define OBJ_FF_WIDTH 50

void setup_free_fall();
int screen_free_fall();
object_free_fall create_object_temp(int *mx, int *my, int height, int width);
void create_object(int *mx, int *my);
void create_object_move(int *mx, int *my);
bool is_clicked_objs(int mx, int my, object_free_fall obj);
bool is_clicked_menu(int mx, int my, Button obj);
