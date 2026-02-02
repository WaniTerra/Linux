#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
    float x, y, width, height, speed;
    SDL_Color color;
    float results[4];
} object;

typedef struct
{
    float x, y;
    const char *text;
    TTF_Font *font;
    SDL_Color color;
} Label;

extern object player;
extern object menu;
extern object menu_free_fall;


void draw_square(SDL_Renderer *renderer, const object obj);
void draw_text(SDL_Renderer *renderer, Label lbl);
