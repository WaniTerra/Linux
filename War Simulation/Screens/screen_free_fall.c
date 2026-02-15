#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "screen_free_fall.h"
#include "main_menu.h"
#include "object.h"

Button btn_start;
Button surface;

object_free_fall *objs = NULL;
int objs_num = 0;
int objs_capacity = 4;

void create_object_temp(int *mx, int *my)
{
    if (objs == NULL)
    {
        objs = malloc(sizeof(object_free_fall) * objs_capacity);
    }
    
    if (objs_num == objs_capacity)
    {
        objs_capacity *= 2;

        object_free_fall *temp = realloc(objs, sizeof(object_free_fall) * objs_capacity);

        if (temp == NULL)
        {
            fprintf(stderr, "No space!\n");
        }
        else
        {
            objs = temp;
        }
    }

    srand(time(NULL));
    object_free_fall temp;
    temp.x = *mx;
    temp.y = *my;

    int color[objs_num + 1];
    for (int i = 0; i < objs_num + 1; i++)
    {
        int num = rand() % 255 + 1;
        color[i] = num;
    }

    temp.color = (SDL_Color){color[0], color[1], color[2], 120};
    temp.height = 100;
    temp.width = 100;
    temp.speed = 0;
    temp.active = true;

    objs[objs_num] = temp;
    objs_num++;
}

void setup_free_fall()
{

    if (objs == NULL)
    {
        objs_capacity = 4;
        objs = malloc(sizeof(object_free_fall) * 4);
    }

    btn_start = (Button){.x = 1400, .y = 750, .height = 80, .width = 120, .color = (SDL_Color){255, 0, 0, 255}};
    menu.y = 200;
    menu.height = 700;
    menu.width = 1200;

    surface = (Button){.x = 0, .y = 870, .height = 40, .width = 1200, .color = (SDL_Color){0, 120, 0, 255}};

    if (menu_font)
    {
        Label menu_label = {WIDTH - (WIDTH / 1.65), 35.0f, "Free Fall", global_font, {255, 255, 255, 255}};
        draw_text(renderer, menu_label);

        Label start_label = {1430, 780, "Start", menu_font, {255, 255, 255, 255}};
        draw_text(renderer, start_label);
    }

    draw_square_button(renderer, btn_start);
    draw_square_button(renderer, menu);
    draw_square_button(renderer, surface);
}

int screen_free_fall()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int mx, my;
    uint32_t buttons = SDL_GetMouseState(&mx, &my);
    setup_free_fall();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            free(objs);
            return 1;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                create_object_temp(&mx, &my);
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (!objs[i].active)
        {
            continue;
        }

        draw_square_object_ff(renderer, objs[i]);
    }

    if (is_clicked(mx, my, btn_start) && (buttons & SDL_BUTTON_LMASK))
    {
        btn_start.color = (SDL_Color){100, 0, 0, 255};
    }
    else
    {
    }

    SDL_RenderPresent(renderer);
    return 0;
}