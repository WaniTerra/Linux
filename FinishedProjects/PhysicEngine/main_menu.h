#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "object.h"

#define WIDTH 1600
#define HEIGHT 900

extern uint32_t *buffer;
extern SDL_Texture *texture;
extern SDL_Renderer *renderer;
extern SDL_Window *window;

extern Button btn_start;
extern Button menu;

extern int last_frame_time;

extern TTF_Font *global_font;
extern TTF_Font *menu_font;

void clear_screen(uint32_t color);
void start(void);
void render(void);
void update(float dt);
void setup(void);
bool is_clicked(int mx, int my, Button obj);