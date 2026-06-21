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
#include "experiments.h"

Button btn_start;
Button surface;
Button panel;

object_free_fall *objs = NULL;
object_free_fall *obj_move_arr = NULL;
object_free_fall obj_temp;
object_free_fall *ff_clicked = NULL;

int objs_num = 0;
int objs_capacity = 6;

int obj_move_num = 0;
int obj_move_capacity = 6;

bool temp_draw = false;
bool mouse_down = false;
bool clicked = false;
bool setup_st = false;
bool border_crossed = false;

Label menu_label;
Label start_label;

object_free_fall create_object_temp(int *mx, int *my, int height, int width)
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

    temp.width = width;
    temp.height = height;

    temp.x = (float)*mx - (width / 2.0f);
    temp.y = (float)*my - (height / 2.0f);

    int color[3];
    for (int i = 0; i < 3; i++)
    {
        int num = rand() % 255 + 1;
        color[i] = num;
    }

    temp.color = (SDL_Color){color[0], color[1], color[2], 100};
    temp.height = height;
    temp.width = width;
    temp.speed = 0;
    temp.active = true;

    return temp;
}

bool is_clicked_objs(int mx, int my, object_free_fall obj)
{
    return (mx >= obj.x &&
            mx <= obj.x + obj.width &&
            my >= obj.y &&
            my <= obj.y + obj.height);
}

bool is_clicked_menu(int mx, int my, Button obj)
{
    return (mx >= obj.x + OBJ_FF_WIDTH / 2 &&
            mx <= obj.x + obj.width - OBJ_FF_WIDTH / 2 &&
            my >= obj.y + OBJ_FF_HEIGHT / 2 &&
            my <= obj.y + obj.height - OBJ_FF_HEIGHT / 2);
}
void create_object(int *mx, int *my)
{
    object_free_fall temp = create_object_temp(mx, my, 50, 50);
    objs[objs_num] = temp;
    objs_num++;
}

void create_object_move(int *mx, int *my)
{
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

    object_free_fall temp = create_object_temp(mx, my, 5, 5);

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

    draw_square_button(renderer, btn_start);
    draw_square_button(renderer, menu);
    draw_square_button(renderer, surface);
    draw_square_button(renderer, panel);
    draw_text(renderer, menu_label);
    draw_text(renderer, start_label);
}
void setup_objects()
{
    btn_start = (Button){.x = 1400, .y = 750, .height = 80, .width = 120, .color = (SDL_Color){255, 0, 0, 255}};
    menu.y = 200;
    menu.height = 700;
    menu.width = 1200;

    panel = (Button){.x = 1350, .y = 200, .height = 500, .width = 190, .color = menu.color};
    surface = (Button){.x = 0, .y = 870, .height = 40, .width = 1200, .color = (SDL_Color){0, 120, 0, 255}};

    if (menu_font)
    {
        menu_label = (Label) {WIDTH - (WIDTH / 1.65), 35.0f, "Free Fall", global_font, {255, 255, 255, 255}};

        int text_w, text_h;
        TTF_SizeText(menu_font, "Start", &text_w, &text_h);

        int centered_x = btn_start.x + (btn_start.width / 2) - (text_w / 2);
        int centered_y = btn_start.y + (btn_start.height / 2) - (text_h / 2);

        start_label =(Label) {centered_x, centered_y, "Start", menu_font, {255, 255, 255, 255}};
    }
}
int screen_free_fall()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);

    int mx, my;
    uint32_t buttons = SDL_GetMouseState(&mx, &my);
    SDL_Event event;

    if (!setup_st)
    {
        setup_objects();
        SDL_Delay(100);
    }
    setup_free_fall();

    while (SDL_PollEvent(&event))
    {

        SDL_GetMouseState(&mx, &my);
        if (event.type == SDL_QUIT)
        {
            free(objs);
            free(obj_move_arr);
            return 1;
        }
        if (is_clicked_menu(mx, my, menu))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (clicked == false)
                {
                    for (int i = 0; i < objs_num; i++)
                    {
                        clicked = is_clicked_objs(mx, my, objs[i]);
                        if (clicked)
                        {
                            break;
                        }
                    }
                }

                if (event.button.button == SDL_BUTTON_LEFT && !clicked)
                {
                    obj_temp = create_object_temp(&mx, &my, 50, 50);
                    mouse_down = true;
                    temp_draw = true;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && clicked)
                {
                    for (int i = 0; i < objs_num; i++)
                    {
                        ff_clicked = find_ff(mx, my, objs + i);
                        if (ff_clicked == NULL)
                        {
                            continue;
                        }

                        (*ff_clicked).color.a = 180;
                        break;
                    }
                }
            }
        }

        if (event.type == SDL_MOUSEMOTION && mouse_down)
        {

            create_object_move(&event.motion.x, &event.motion.y);

            if (is_clicked_menu(!event.motion.x, event.motion.y, menu))
            {
                border_crossed = true;
            }
            else
            {
                border_crossed = false;
            }
        }
        if (is_clicked_menu(mx, my, menu))
        {
            if (event.type == SDL_MOUSEBUTTONUP && setup_st)
            {
                if (event.button.button == SDL_BUTTON_LEFT && !clicked)
                {
                    create_object(&mx, &my);
                    objs[objs_num - 1].color = obj_temp.color;
                    objs[objs_num - 1].color.a = 255;

                    for (int i = 0; i < obj_move_num; i++)
                    {
                        if (!obj_move_arr[i].active)
                        {
                            continue;
                        }
                        obj_move_arr[i].color = menu.color;
                        draw_square_object_ff(renderer, obj_move_arr[i]);
                        temp_draw = false;
                    }

                    obj_move_num = 0;
                    mouse_down = false;
                }
                if (event.button.button == SDL_BUTTON_LEFT && clicked)
                {
                    if (!border_crossed)
                    {
                        (*ff_clicked).x = mx - ((*ff_clicked).width / 2.0f);
                        (*ff_clicked).y = my - ((*ff_clicked).height / 2.0f);
                    }

                    (*ff_clicked).color.a = 255;
                }
                clicked = false;
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

    if (temp_draw)
        draw_square_object_ff(renderer, obj_temp);

    if (is_clicked(mx, my, btn_start) && (buttons & SDL_BUTTON_LMASK))
    {
        btn_start.color = (SDL_Color){100, 0, 0, 255};
        for (int i = 0; i < objs_num; i++)
        {
            free_fall((objs + i),(*(objs + i)).y - surface.y, 1, 10, 10, false, 1, 1,1);
        }
        
    }
    else
    {
    }

    setup_st = true;
    SDL_RenderPresent(renderer);
    return 0;
}