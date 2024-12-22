#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <SDL/SDL_video.h>

void drawBoardToSurface(Board *b, SDL_Surface * screen);
#endif // !GAME_H
