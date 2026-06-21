
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "object.h"
#include "main_menu.h"

void draw_square_button(SDL_Renderer *renderer, const Button obj)
{
    SDL_Rect rect = {
        (int)obj.x,
        (int)obj.y,
        obj.width,
        obj.height};

    SDL_SetRenderDrawColor(renderer, obj.color.r, obj.color.g, obj.color.b, obj.color.a);

    SDL_RenderFillRect(renderer, &rect);
}

void draw_square_object_ff(SDL_Renderer *renderer, const object_free_fall obj)
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

object_free_fall *find_ff(int mx, int my, object_free_fall *obj)
{

    if (mx >= obj->x &&
        mx <= obj->x + obj->width &&
        my >= obj->y &&
        my <= obj->y + obj->height)
    {
        return obj;
    }

    return NULL;
}
