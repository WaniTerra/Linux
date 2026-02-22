#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct object_free_fall
{
    float x, y, width, height, speed;
    SDL_Color color;
    float results[4];
    bool active;
} object_free_fall;

typedef struct Label
{
    float x, y;
    const char *text;
    TTF_Font *font;
    SDL_Color color;
} Label;

typedef struct Button
{
    float x, y, width, height;
    SDL_Color color;
} Button;

extern Button menu;
extern Button menu_free_fall;

void draw_square_button(SDL_Renderer *renderer, const Button obj);
void draw_square_object_ff(SDL_Renderer *renderer, const object_free_fall obj);

void draw_text(SDL_Renderer *renderer, Label lbl);
object_free_fall *find_ff(int mx, int my, object_free_fall *obj);
#endif
