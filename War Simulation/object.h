#include <stdint.h>

typedef struct
{
    float x, y, width, height, speed;
    uint32_t color;
} square;


extern square sq;

void draw_square(int x, int y, int w, int h, uint32_t color);
