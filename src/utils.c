#include "utils.h"
#include <stdio.h>

void printVec2d(Vec2D vec) {
    printf("(%d, %d)\n", vec.x, vec.y);
}

Vec2D getVecFromDirection(Direction dir) {
    Vec2D vec = {0,0};
    switch (dir) {
        case DIRECTION_UP:
            vec.y = -1;
            break;
        case DIRECTION_DOWN:
            vec.y = 1;
            break;
        case DIRECTION_RIGHT:
            vec.x = 1;
            break;
        case DIRECTION_LEFT:
            vec.x = -1;
            break;
    }
    return vec;
}

Vec2D vecSum(Vec2D vec1, Vec2D vec2) {
    Vec2D v = {
        .x = vec1.x + vec2.x,
        .y = vec1.y + vec2.y
    };
    return v;
}
