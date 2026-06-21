#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

#define RADAR_WIDTH 160
#define RADAR_HEIGHT 120
#define RADAR_X (WIDTH - RADAR_WIDTH - 10)
#define RADAR_Y (HEIGHT - RADAR_HEIGHT - 10)

#define MAX_BULLETS 20
#define MAX_PARTICLES 100

typedef struct
{
    float x, y, width, height, speed;
    uint32_t color;
} Player;

typedef struct
{
    float x, y, width, height, speed;
    bool is_active;
} Projectile;

typedef struct
{
    float x, y, width, height;
    bool is_active;
    uint32_t color;
} Target;

typedef struct
{
    float x, y;
    float vx, vy;
    float life;
    bool is_active;
    uint32_t color;
} Particle;

uint32_t *buffer;
SDL_Texture *texture;
SDL_Renderer *renderer;
SDL_Window *window;

Player player;
Projectile bullets[MAX_BULLETS];
Target target;
Particle particles[MAX_PARTICLES];

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

void draw_radar()
{
    for (int y = 0; y < RADAR_HEIGHT; y++)
    {
        for (int x = 0; x < RADAR_WIDTH; x++)
        {
            int screen_x = RADAR_X + x;
            int screen_y = RADAR_Y + y;
            buffer[(screen_y * WIDTH) + screen_x] = 0xFF002200;
        }
    }

    float scale_x = (float)RADAR_WIDTH / WIDTH;
    float scale_y = (float)RADAR_HEIGHT / HEIGHT;

    int p_radar_x = RADAR_X + (player.x * scale_x);
    int p_radar_y = RADAR_Y + (player.y * scale_y);
    draw_rect(p_radar_x, p_radar_y, 4, 4, 0xFF0000FF);

    int t_radar_x = RADAR_X + (target.x * scale_x);
    int t_radar_y = RADAR_Y + (target.y * scale_y);
    draw_rect(t_radar_x, t_radar_y, 4, 4, 0xFFFF0000);

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].is_active)
        {
            int b_radar_x = RADAR_X + (bullets[i].x * scale_x);
            int b_radar_y = RADAR_Y + (bullets[i].y * scale_y);
            draw_rect(b_radar_x, b_radar_y, 2, 2, 0xFFFFFFFF);
        }
    }
}

bool check_collision(float x1, float y1, float w1, float h1,
                     float x2, float y2, float w2, float h2)
{
    return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

void explode(float x, float y, uint32_t color)
{
    int particle_count = 20;
    int spawned = 0;

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particles[i].is_active)
        {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].vx = ((rand() % 200) - 100) * 2.0f;
            particles[i].vy = ((rand() % 200) - 100) * 2.0f;
            particles[i].life = 1.0f;
            particles[i].color = color;
            particles[i].is_active = true;
            spawned++;
            if (spawned >= particle_count)
                break;
        }
    }
}

void setup()
{
    srand(time(NULL));

    player.x = WIDTH / 2 - 20;
    player.y = HEIGHT - 60;
    player.width = 40;
    player.height = 40;
    player.speed = 300;
    player.color = 0xFFFF0000;

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].is_active = false;
        bullets[i].width = 8;
        bullets[i].height = 15;
        bullets[i].speed = 500;
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].is_active = false;
    }

    target.width = 50;
    target.height = 50;
    target.x = 100;
    target.y = 100;
    target.is_active = true;
    target.color = 0xFF00FF00;
}

void shoot_bullet()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].is_active)
        {
            bullets[i].x = player.x + (player.width / 2) - (bullets[i].width / 2);
            bullets[i].y = player.y;
            bullets[i].is_active = true;
            break;
        }
    }
}

void respawn_target()
{
    target.x = 50 + rand() % (WIDTH - 100);
    target.y = 50 + rand() % (HEIGHT / 2);
}

void update(float dt)
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_A])
        player.x -= player.speed * dt;
    if (keystate[SDL_SCANCODE_D])
        player.x += player.speed * dt;

    if (player.x < 0)
        player.x = 0;
    if (player.x + player.width > WIDTH)
        player.x = WIDTH - player.width;

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].is_active)
        {
            bullets[i].y -= bullets[i].speed * dt;

            if (bullets[i].y < -20)
            {
                bullets[i].is_active = false;
                continue;
            }

            if (check_collision(bullets[i].x, bullets[i].y, bullets[i].width, bullets[i].height,
                                target.x, target.y, target.width, target.height))
            {

                explode(target.x + target.width / 2, target.y + target.height / 2, target.color);

                bullets[i].is_active = false;
                respawn_target();
            }
        }
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].is_active)
        {
            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
            particles[i].life -= dt * 2.0f;

            if (particles[i].life <= 0)
            {
                particles[i].is_active = false;
            }
        }
    }
}

void render()
{
    clear_screen(0xFF101010);

    draw_rect((int)player.x, (int)player.y, (int)player.width, (int)player.height, player.color);

    draw_rect((int)target.x, (int)target.y, (int)target.width, (int)target.height, target.color);

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].is_active)
        {
            draw_rect((int)bullets[i].x, (int)bullets[i].y, (int)bullets[i].width, (int)bullets[i].height, 0xFFFFFF00);
        }
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].is_active)
        {
            draw_rect((int)particles[i].x, (int)particles[i].y, 3, 3, particles[i].color);
        }
    }

    draw_radar();

    SDL_UpdateTexture(texture, NULL, buffer, (int)(WIDTH * sizeof(uint32_t)));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Real Time Shooter Physic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                    shoot_bullet();
            }
        }

        int time_to_wait = 16 - (SDL_GetTicks() - last_frame_time);
        if (time_to_wait > 0 && time_to_wait <= 16)
            SDL_Delay(time_to_wait);
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