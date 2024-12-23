#include "game.h"
#include "board.h"
#include "entity.h"
#include "tile.h"
#include "utils.h"
#include <SDL/SDL_video.h>
#include <stdio.h>

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

    for (x=0; x<b->entity_count; x++) {
        Entity e = b->entities[x];
        Color col = ENTITY_DATA[e.type].color;
        SDL_Surface * rectangle = NULL ;
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXEL_SIZE, PIXEL_SIZE, 32, 0, 0, 0, 0) ;
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, col.r, col.g, col.b));

        SDL_Rect position = {
            .x = e.pos.x * PIXEL_SIZE,
            .y = e.pos.y * PIXEL_SIZE
        };
        SDL_BlitSurface(rectangle, NULL, screen, &position);
    }

    SDL_Flip(screen);
}

void movePlayer(Board *b, Direction dir) {
    Vec2D vec = getVecFromDirection(dir);
    for (int i=0; i<b->entity_count; i++) {
        Entity * e = &b->entities[i];
        if (e->type == PLAYER_ENTITY_TYPE) {
            Vec2D new_pos = vecSum(e->pos, vec);
            e->pos = new_pos;
        }
    }
}
