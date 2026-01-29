
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "object.h"
#include "screen.h"

square sq;

void draw_square(int x, int y, int w, int h, uint32_t color)
{
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < h; col++)
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