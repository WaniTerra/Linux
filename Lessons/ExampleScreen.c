#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
    float x, y;
    float width, height;
    float speed;
    uint32_t color;
} Player;

uint32_t *buffer;
SDL_Texture *texture;
SDL_Renderer *renderer;
SDL_Window *window;
Player player;

int last_frame_time = 0;

void clear_screen(uint32_t color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        buffer[i] = color;
}

void draw_rect(int x, int y, int w, int h, uint32_t color)
{
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            int current_y = y + row;
            int current_x = x + col;
            if (current_x >= 0 && current_x < WIDTH && current_y >= 0 && current_y < HEIGHT)
            {
                buffer[(current_y * WIDTH) + current_x] = color;
            }
        }
    }
}

void setup()
{
    player.x = WIDTH / 2 - 20;
    player.y = HEIGHT / 2 - 20;
    player.width = 40;
    player.height = 40;

    player.speed = 300;
    player.color = 0xFFFF0000;
}

void update(float dt)
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W])
        player.y -= player.speed * dt;
    if (keystate[SDL_SCANCODE_S])
        player.y += player.speed * dt;
    if (keystate[SDL_SCANCODE_A])
        player.x -= player.speed * dt;
    if (keystate[SDL_SCANCODE_D])
        player.x += player.speed * dt;

    if (player.x < 0)
        player.x = 0;
    if (player.y < 0)
        player.y = 0;
    if (player.x + player.width > WIDTH)
        player.x = WIDTH - player.width;
    if (player.y + player.height > HEIGHT)
        player.y = HEIGHT - player.height;
}

void render()
{
    clear_screen(0xFF000000);
    draw_rect((int)player.x, (int)player.y, (int)player.width, (int)player.height, player.color);
    SDL_UpdateTexture(texture, NULL, buffer, (int)(WIDTH * sizeof(uint32_t)));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Delta Time Motoru", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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
    return 0;
}