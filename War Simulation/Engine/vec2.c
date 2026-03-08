#include <stdio.h>
#include <vec2.h>
#include <math.h>
Vec2 vec2_add(Vec2 a, Vec2 b)
{
    return (Vec2){.x = a.x + b.x, .y = a.y + b.y};
}

Vec2 vec2_sub(Vec2 a, Vec2 b)
{
    return (Vec2){.x = a.x - b.x, .y = a.y - b.y};
}

Vec2 vec2_mul(Vec2 v, float scaler)
{
    return (Vec2){.x = v.x * scaler, .y = v.y * scaler};
}

float vec2_length(Vec2 v)
{
    return sqrt(v.x * v.x - v.y * v.y);
}

Vec2 vec2_normalize(Vec2 v);
float vec2_dot(Vec2 a, Vec2 b);
float vec2_distance(Vec2 a, Vec2 b);
