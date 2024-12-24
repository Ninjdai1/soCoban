#include "game.h"
#include "board.h"
#include "entity.h"
#include "tile.h"
#include "ui/button.h"
#include "utils.h"
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic ignored "-Wswitch"

Game * initGame(SDL_Surface *screen) {
    Game * game = malloc(sizeof(Game));

    game->screen = screen;
    game->current_level = 1;

    GameFlags flags = {
        .draw = 0,
        .running = 1
    };

    game->flags = flags;

    game->button_count = 1;
    game->buttons = malloc(sizeof(Button) * game->button_count);

    Button btn_reset = {
        .id = "btn_reset",
        .name = "Reset",
        .pos = {640, 640},
        .size = {320, 32},
        .callback = resetGameBoard,
        .flags = {
            .refreshAfterCallback = 1,
            .visible = 1,
            .enabled = 1
        }
    };
    game->buttons[0] = btn_reset;
    
    char level_path[28];
    sprintf(level_path, "levels/level%d.scb", game->current_level);
    game->board = loadBoardFromFile(level_path);

    return game;
}

void runGame(Game *game) {
    Button *btn;
    drawGameToSurface(game);
    SDL_Event event;
    while (game->flags.running) {
        game->flags.draw = 0;
        //SDL_PollEvent(&event);
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                game->flags.running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case 'q':
                        game->flags.running = 0;
                        break;
                    case 'r':
                        resetGameBoard(game);
                        game->flags.draw = 1;
                        break;
                    case SDLK_UP:
                        movePlayer(game->board, DIRECTION_UP);
                        game->flags.draw = 1;
                        break;
                    case SDLK_DOWN:
                        movePlayer(game->board, DIRECTION_DOWN);
                        game->flags.draw = 1;
                        break;
                    case SDLK_RIGHT:
                        movePlayer(game->board, DIRECTION_RIGHT);
                        game->flags.draw = 1;
                        break;
                    case SDLK_LEFT:
                       movePlayer(game->board, DIRECTION_LEFT);
                        game->flags.draw = 1;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                btn = getButtonAtPos(game, event.button.x, event.button.y);
                if ((btn != NULL) && (btn->flags.enabled)) {
                    btn->callback(game);
                    if (btn->flags.refreshAfterCallback) game->flags.draw = 1;
                };
                break;
        }
        if (checkWin(game->board)) {
            printf("Victoire ! Niveau %d terminé !\n", game->current_level);
            if (game->current_level < MAX_LEVEL) {
                game->current_level++;
                char level_path[28];
                sprintf(level_path, "levels/level%d.scb", game->current_level);
                freeBoard(game->board);
                game->board = loadBoardFromFile(level_path);
                game->flags.draw = 1;
            } else {
                printf("Jeu terminé ! Félicitations");
                game->flags.running = 0;
            }
        }
        if (game->flags.draw==1) {
            drawGameToSurface(game);
        }
    }
}

void resetGameBoard(Game *game) {
    initEntities(game->board);
}

void freeGame(Game *game) {
    freeBoard(game->board);
    free(game->buttons);
    free(game);
}

void drawGameToSurface(Game *game) {
    drawBoardToSurface(game->board, game->screen);

    for (int i=0; i<game->button_count; i++) {
        drawButtonToSurface(&game->buttons[i], game->screen);
    }
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

Button * getButtonAtPos(Game *game, int x, int y) {
    for (int i=0; i<game->button_count; i++) {
        Button *b = &game->buttons[i];
        if (
            (b->pos.x <= x) && (x <= b->pos.x + b->size.x)
            && (b->pos.y <= y) && (y <= b->pos.y + b->size.y)
        ) return b;
    }
    return NULL;
}
