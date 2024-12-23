#ifndef UTILS_H
#define UTILS_H

typedef enum Direction_E {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_RIGHT,
    DIRECTION_LEFT
} Direction;

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

Vec2D getVecFromDirection(Direction dir);

Vec2D vecSum(Vec2D vec1, Vec2D vec2);

#endif // !UTILS_H
