#ifndef UTILS_H
#define UTILS_H

typedef struct Vec2D_I {
    int x;
    int y;
} Vec2D;

void printVec2d(Vec2D vec);

typedef struct Color_I {
    int r;
    int g;
    int b;
} Color;

#endif // !UTILS_H
