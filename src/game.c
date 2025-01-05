#include "game.h"
#include "board.h"
#include "entity.h"
#include "tile.h"
#include "ui/component.h"
#include "utils.h"
#include "config.h"
#include <SDL/SDL_events.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#pragma GCC diagnostic ignored "-Wswitch"

// Fonctions locales utilisées par les "Components"
void toggleFileMenu(Game *game) {
    game->flags.show_topbar = !game->flags.show_topbar;
    toggleComponent(&game->components[2], game->flags.show_topbar);
    game->flags.clear = 1;
}

// Fonctions de game.h
Game * initGame(SDL_Surface *screen, TTF_Font *game_font) {
    Game * game = malloc(sizeof(Game));

    game->screen = screen;
    game->game_font = game_font;
    game->current_level = 1;

    GameFlags flags = {
        .draw = 0,
        .running = 1,
        .clear = 0,
        .show_topbar = 0
    };

    game->flags = flags;

    game->button_count = 3;
    game->components = malloc(sizeof(Component) * game->button_count);

    Component txt_win = {
        DEFAULT_COMPONENT_INITIALIZERS,
        .type = TEXT_DISPLAY,
        .id = "txt_win",
        .text = "Victoire !",
        .pos = {256, 128},
        .size = {128, 32},
        .flags = {
            .refreshAfterCallback = 0,
            .visible = 0,
            .enabled = 0
        }
    };
    Component btn_options = {
        DEFAULT_COMPONENT_INITIALIZERS,
        .type = BUTTON,
        .id = "btn_options",
        .text = "Options",
        .pos = {0, 0},
        .size = {128, 32},
        .callback = toggleFileMenu,
        .flags = {
            .refreshAfterCallback = 1,
            .visible = 1,
            .enabled = 1
        }
    };
    Component btn_reset = {
        .type = BUTTON,
        .id = "btn_reset",
        .text = "Reset",
        .pos = {0, 40},
        .size = {96, 32},
        .callback = resetGameBoard,
        .bg_color = getDefaultColor(COLOR_RED),
        .fg_color = getDefaultColor(COLOR_WHITE),
        .flags = {
            .refreshAfterCallback = 1,
            .visible = 0,
            .enabled = 0
        }
    };
    game->components[0] = txt_win;
    game->components[1] = btn_options;
    game->components[2] = btn_reset;
    
    char level_path[28];
    sprintf(level_path, "levels/level%d.scb", game->current_level);
    game->board = loadBoardFromFile(level_path);

    return game;
}

void runGame(Game *game) {
    Component *btn;
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
                    #if DEBUG
                    printf("Clic sur %s\n", btn->id);
                    #endif /* if DEBUG */
                    btn->callback(game);
                    if (btn->flags.refreshAfterCallback) game->flags.draw = 1;
                };
                break;
        }
        if (checkWin(game->board)) {
            printf("Victoire ! Niveau %d terminé !\n", game->current_level);
            if (game->current_level < MAX_LEVEL) {
                game->flags.clear = 1;
                game->current_level++;
                char level_path[28];
                sprintf(level_path, "levels/level%d.scb", game->current_level);
                freeBoard(game->board);
                game->board = loadBoardFromFile(level_path);
                game->flags.draw = 1;
            } else {
                printf("Jeu terminé ! Félicitations\n");
                game->components[1].flags.visible = 1;
                game->flags.running = 0;
            }
        }
        if (game->flags.clear) {
            SDL_Surface * rectangle = NULL ;
            rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, game->screen->w, game->screen->h, 32, 0, 0, 0, 0);
            SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 0, 0, 0));

            SDL_Rect position = {
                .x = 0,
                .y = 0
            };
            SDL_BlitSurface(rectangle, NULL, game->screen, &position);
            game->flags.clear = 0;
        }
        if (game->flags.draw) {
            drawGameToSurface(game);
        }
    }
    SDL_Delay(2000);
}

void resetGameBoard(Game *game) {
    initEntities(game->board);
    toggleFileMenu(game);
}

void freeGame(Game *game) {
    TTF_CloseFont(game->game_font);
    freeBoard(game->board);
    free(game->components);
    free(game);
}

void drawGameToSurface(Game *game) {
    drawBoardToSurface(game->board, game->screen);

    for (int i=0; i<game->button_count; i++) {
        if (game->components[i].flags.visible) {
            drawComponentToSurface(&game->components[i], game->screen, game->game_font);
        }
    }
    SDL_Flip(game->screen);
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

Component * getButtonAtPos(Game *game, int x, int y) {
    for (int i=0; i<game->button_count; i++) {
        Component *b = &game->components[i];
        #if DEBUG
        printf("Checking for %s at (%d, %d)\n", b->id, x, y);
        printf("x: %d, y: %d, w: %d, h: %d\n", b->pos.x, b->pos.y, b->size.x, b->size.y);
        #endif/* if DEBUG */
        if (
            (b->type == BUTTON)
            && (b->pos.x <= x) && (x <= b->pos.x + b->size.x)
            && (b->pos.y <= y) && (y <= b->pos.y + b->size.y)
        ) {
            #if DEBUG
            printf("Found %s for (%d, %d)\n", b->id, x, y);
            #endif/* if DEBUG */
            return b;
        }
    }
    return NULL;
}
