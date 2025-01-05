#include "utils.h"
#include <SDL/SDL_video.h>
#include <stdio.h>

SDL_Color getDefaultColor(DefaultColor c) {
    SDL_Color color = {0,0,0};
    switch (c) {
        case COLOR_WHITE:
            color.r = 210;
            color.g = 210;
            color.b = 210;
            break;
        case COLOR_GREY:
            color.r = 125;
            color.g = 125;
            color.b = 125;
            break;
        case COLOR_BLACK:
            color.r = 0;
            color.g = 0;
            color.b = 0;
            break;
        case COLOR_RED:
            color.r = 205;
            color.g = 0;
            color.b = 0;
            break;
        case COLOR_GREEN:
            color.r = 0;
            color.g = 205;
            color.b = 0;
            break;
        case COLOR_BLUE:
            color.r = 0;
            color.g = 205;
            color.b = 0;
            break;
    }
    return color;
}

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
