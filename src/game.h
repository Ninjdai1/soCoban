#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "utils.h"
#include <SDL/SDL_video.h>

void drawBoardToSurface(Board *b, SDL_Surface * screen);

void movePlayer(Board *b, Direction dir);

#endif // !GAME_H
