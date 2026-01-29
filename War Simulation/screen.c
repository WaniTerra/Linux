#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "screen.h"
#include "object.h"

void clear_screen(uint32_t color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        buffer[i] = color;
}

int last_frame_time = 0;
uint32_t *buffer;
SDL_Texture *texture;
SDL_Renderer *renderer;
SDL_Window *window;

void render()
{
    clear_screen(0xFF000000);
    draw_square((int)sq.x, (int)sq.y, (int)sq.width, (int)sq.height, sq.color);
    SDL_UpdateTexture(texture, NULL, buffer, (int)(WIDTH * sizeof(uint32_t)));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void update(float dt)
{
}

void setup()
{
    sq.x = 100;
    sq.y = 100;
    sq.height = 20;
    sq.width = 20;
    sq.color = 0xFFFF0000;
}
void start()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("War Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    buffer = (uint32_t *)malloc(sizeof(uint32_t) * WIDTH * HEIGHT);

    setup();

    bool is_running = true;
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
