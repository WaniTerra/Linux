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
object_free_fall *obj_move_arr = NULL;
object_free_fall obj_temp;
int objs_num = 0;
int objs_capacity = 6;

int obj_move_num = 0;
int obj_move_capacity = 6;

bool mouse_down = false;

bool setup_st = false;

object_free_fall create_object_temp(int *mx, int *my)
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

    srand(SDL_GetTicks());
    object_free_fall temp;
    temp.x = *mx;
    temp.y = *my;

    int color[3];
    for (int i = 0; i < 3; i++)
    {
        int num = rand() % 255 + 1;
        color[i] = num;
    }

    temp.color = (SDL_Color){color[0], color[1], color[2], 100};
    temp.height = 100;
    temp.width = 100;
    temp.speed = 0;
    temp.active = true;

    return temp;
}

void create_object(int *mx, int *my)
{
    object_free_fall temp = create_object_temp(mx, my);
    objs[objs_num] = temp;
    objs_num++;
}

void create_object_move(int *mx, int *my)
{
    object_free_fall temp = create_object_temp(mx, my);
    obj_move_arr[obj_move_num] = temp;
    obj_move_num++;
}

void setup_free_fall()
{

    if (objs == NULL)
    {
        objs_capacity = 6;
        objs = malloc(sizeof(object_free_fall) * 6);
    }
    if (obj_move_arr == NULL)
    {
        obj_move_capacity = 6;
        obj_move_arr = malloc(sizeof(object_free_fall) * 6);
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);

    int mx, my;
    uint32_t buttons = SDL_GetMouseState(&mx, &my);
    if (setup_st == false)
        setup_free_fall();

    setup_st = false;
    SDL_Event event;

    if (obj_move_num == obj_move_capacity)
    {
        obj_move_capacity *= 2;
        object_free_fall *temp = realloc(obj_move_arr, sizeof(object_free_fall) * obj_move_capacity);

        if (temp == NULL)
        {
            fprintf(stderr, "No space!\n");
        }
        else
        {
            obj_move_arr = temp;
        }
    }
    else if (obj_move_arr == NULL)
    {
        obj_move_capacity = 6;
        obj_move_arr = malloc(sizeof(object_free_fall) * 6);
    }

    while (SDL_PollEvent(&event))
    {
        SDL_GetMouseState(&mx, &my);
        if (event.type == SDL_QUIT)
        {
            free(objs);
            free(obj_move_arr);
            return 1;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_down = true;
                obj_temp = create_object_temp(&mx, &my);
                draw_square_object_ff(renderer, obj_temp);
            }
        }
        if (event.type == SDL_MOUSEMOTION && mouse_down)
        {

            obj_temp.x = event.motion.x;
            obj_temp.y = event.motion.y;
            usleep(1000000);
            create_object_move(&event.motion.x, &event.motion.y);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                create_object(&mx, &my);

                for (int i = 0; i < obj_move_num; i++)
                {
                    if (!obj_move_arr[i].active)
                    {
                        continue;
                    }
                    obj_move_arr[i].color = menu.color;
                    draw_square_object_ff(renderer, obj_move_arr[i]);
                }

                obj_move_num = 0;
                mouse_down = false;
            }
        }
    }

    for (int i = 0; i < objs_num; i++)
    {
        if (!objs[i].active)
        {
            continue;
        }

        draw_square_object_ff(renderer, objs[i]);
    }

    for (int i = 0; i < obj_move_num; i++)
    {
        if (!obj_move_arr[i].active)
        {
            continue;
        }

        draw_square_object_ff(renderer, obj_move_arr[i]);
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