#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "main_menu.h"
#include "screen_free_fall.h"
#include "object.h"

bool experiment[] = {0, 0};
bool exp_on_board = 0;

int last_frame_time = 0;
uint32_t *buffer;
SDL_Texture *texture;
SDL_Renderer *renderer;
SDL_Window *window;
bool is_running = true;

Button menu;
Button menu_free_fall;

TTF_Font *global_font = NULL;
TTF_Font *menu_font = NULL;

bool is_clicked(int mx, int my, Button obj)
{
    return (mx >= obj.x &&
            mx <= obj.x + obj.width &&
            my >= obj.y &&
            my <= obj.y + obj.height);
}
bool is_clicked_(int mx, int my, Button obj)
{
    return (mx >= obj.x &&
            mx <= obj.x + obj.width &&
            my >= obj.y &&
            my <= obj.y + obj.height);
}

void menu_main()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_square_button(renderer, menu);
    draw_square_button(renderer, menu_free_fall);
    if (global_font)
    {
        Label menu_label = {WIDTH - (WIDTH / 1.75), 35.0f, "MENU", global_font, {255, 255, 255, 255}};
        draw_text(renderer, menu_label);
    }

    if (menu_font)
    {
        Label menu_label = {30, 350, "Free Fall", menu_font, {255, 255, 255, 255}};
        draw_text(renderer, menu_label);
    }

    SDL_RenderPresent(renderer);
}
void render()
{
    menu_main();
}
void update(float dt)
{

    int mx, my;
    uint32_t buttons = SDL_GetMouseState(&mx, &my);

    if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) && is_clicked(mx, my, menu_free_fall))
    {
        menu_free_fall.color = (SDL_Color){20, 20, 0, 100};
        experiment[0] = 1;
        exp_on_board = 1;
    }
    else
    {
        menu_free_fall.color = (SDL_Color){255, 0, 0, 255};
    }

    if (exp_on_board)
    {
        for (int i = 0; i < 2; i++)
        {
            if (experiment[i] == 1)
            {
                if (i == 0)
                {
                    while (1)
                    {
                        if (screen_free_fall() == 1)
                        {
                            is_running = false;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        render();
    }
}
void setup()
{

    menu.x = 0;
    menu.y = 300;
    menu.height = 400;
    menu.width = 1600;
    menu.color = (SDL_Color){211, 211, 211, 255};

    menu_free_fall.x = 20;
    menu_free_fall.y = 320;
    menu_free_fall.height = 80;
    menu_free_fall.width = 120;
    menu_free_fall.color = (SDL_Color){45, 211, 211, 255};

    global_font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 100);
    if (!global_font)
    {
        printf("No Font: %s\n", TTF_GetError());
    }

    menu_font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
    if (!menu_font)
    {
        printf("No Font: %s\n", TTF_GetError());
    }
}
void start()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("War Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    buffer = (uint32_t *)malloc(sizeof(uint32_t) * WIDTH * HEIGHT);

    TTF_Init();
    setup();

    SDL_Event event;
    while (is_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                is_running = false;
        }
        int time_to_wait = 16 - (SDL_GetTicks() - last_frame_time);

        // Waiting if too fast
        if (time_to_wait > 0 && time_to_wait <= 16)
        {
            SDL_Delay(time_to_wait);
        }

        float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

        last_frame_time = SDL_GetTicks();

        update(delta_time);
        render();
    }

    free(buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
