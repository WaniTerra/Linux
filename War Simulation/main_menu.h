#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define WIDTH 1600
#define HEIGHT 900

extern uint32_t *buffer;
extern SDL_Texture *texture;
extern SDL_Renderer *renderer;
extern SDL_Window *window;

extern int last_frame_time;

void clear_screen(uint32_t color);
void start(void);
void render(void);
void update(float dt);
void setup(void);