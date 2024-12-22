#include "game.h"
#include "board.h"
#include "tile.h"
#include "utils.h"
#include <SDL/SDL_video.h>

#define PIXEL_SIZE 32
void drawBoardToSurface(Board *b, SDL_Surface *screen) {
    int x, y;
    for (y=0; y < b->size.y; y++) {
        for (x=0; x < b->size.x; x++) {
            SDL_Surface * rectangle = NULL ;
            rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXEL_SIZE, PIXEL_SIZE, 32, 0, 0, 0, 0) ;

            Color tileColor = getTileData(b->data[x][y]).col;
            SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, tileColor.r, tileColor.g, tileColor.b));

            SDL_Rect position = {
                .x = x * PIXEL_SIZE,
                .y = y * PIXEL_SIZE
            };
            SDL_BlitSurface(rectangle, NULL, screen, &position);
        }
    }
    SDL_Flip(screen);
}
