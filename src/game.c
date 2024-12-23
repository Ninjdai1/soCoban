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

            Color tileColor = getTileData(b->static_tiles[x][y]).col;
            SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, tileColor.r, tileColor.g, tileColor.b));

            SDL_Rect position = {
                .x = x * PIXEL_SIZE,
                .y = y * PIXEL_SIZE
            };
            SDL_BlitSurface(rectangle, NULL, screen, &position);
        }
    }

    for (x=0; x<b->box_amount; x++) {
        Vec2D pos = b->box_pos[x];
        SDL_Surface * rectangle = NULL ;
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXEL_SIZE, PIXEL_SIZE, 32, 0, 0, 0, 0) ;
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 255, 0, 0));

        SDL_Rect position = {
            .x = pos.x * PIXEL_SIZE,
            .y = pos.y * PIXEL_SIZE
        };
        SDL_BlitSurface(rectangle, NULL, screen, &position);
    }
    
    SDL_Surface * rectangle = NULL ;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXEL_SIZE, PIXEL_SIZE, 32, 0, 0, 0, 0) ;
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 255, 255, 0));

    SDL_Rect position = {
        .x = b->player_pos.x * PIXEL_SIZE,
        .y = b->player_pos.y * PIXEL_SIZE
    };
    SDL_BlitSurface(rectangle, NULL, screen, &position);

    SDL_Flip(screen);
}
