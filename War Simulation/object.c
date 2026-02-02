
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "object.h"
#include "main_menu.h"

void draw_square(SDL_Renderer *renderer, const object obj)
{
    SDL_Rect rect = {
        (int)obj.x,
        (int)obj.y,
        obj.width,
        obj.height};

    SDL_SetRenderDrawColor(renderer, obj.color.r, obj.color.g, obj.color.b, obj.color.a);

    SDL_RenderFillRect(renderer, &rect);
}
void draw_text(SDL_Renderer *renderer, Label lbl)
{
    SDL_Surface *surface = TTF_RenderText_Solid(lbl.font, lbl.text, lbl.color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = {(int)lbl.x, (int)lbl.y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}