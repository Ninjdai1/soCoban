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

            Color tileColor = getTileData(getTile(b, x, y)).col;
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
        if (e.type == BOX_ENTITY_TYPE && isGoalTile(getTile(b, e.pos.x, e.pos.y))) {
            col.b = 125;
        }
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
            Tile t = getTile(b, new_pos.x, new_pos.y);
            if (!getTileData(t).collision) {
                Entity * ent = getEntity(b, new_pos.x, new_pos.y);
                if (ent==NULL) {
                    e->pos = new_pos;
                } else {
                    if (ent->type==BOX_ENTITY_TYPE) {
                        if(moveEntity(b, ent, dir)) {
                            e->pos = new_pos;
                        }
                    }
                }
            }
        }
    }
}

Bool moveEntity(Board *b, Entity *e, Direction dir) {
    Vec2D vec = getVecFromDirection(dir);
    Vec2D new_pos = vecSum(e->pos, vec);
    Tile t = getTile(b, new_pos.x, new_pos.y);
    if (!getTileData(t).collision) {
        Entity * ent = getEntity(b, new_pos.x, new_pos.y);
        if (ent==NULL) {
            e->pos = new_pos;
        } else {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
