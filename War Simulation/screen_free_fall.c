#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "main_menu.h"
#include "object.h"

void setup_free_fall()
{
    object start = {.x = 800, .y = 900, .height = 20, .width = 40, .color = (SDL_Color){255, 0, 0, 255}};
}

object object_free_fall(int *mx, int *my)
{
    object temp;
    temp.x = *mx;
    temp.y = *my;
    temp.color = (SDL_Color){255, 255, 255, 255};
    temp.height = 10;
    temp.width = 10;
    temp.speed = 0;
    temp.results;

    return temp;
}
void screen_free_fall()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (menu_font)
    {
        Label menu_label = {10, 400, "Free Fall", menu_font, {255, 255, 255, 255}};
        draw_text(renderer, menu_label);
        Label start_label = {790, 890, "Free Fall", menu_font, {255, 255, 255, 255}};
        draw_text(renderer, start_label);
    }

    int mx, my;
    uint32_t buttons = SDL_GetMouseState(&mx, &my);
    object temp = object_free_fall(&mx, &my);

    draw_square(renderer, temp);
    draw_square(renderer, start);

    if (is_clicked(&mx, &my, start))
    {
        start.color = (SDL_Color){100, 0, 0, 255};
    }
    else
    {
    }

    SDL_RenderPresent(renderer);
}