#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "utils.h"
#include "ui/button.h"
#include <SDL/SDL_video.h>

#define MAX_LEVEL 3

typedef struct GameFlags_I {
    uint32_t running:1;
    uint32_t draw:1;
} GameFlags;

typedef struct Game_I {
    SDL_Surface * screen;
    Board * board;
    GameFlags flags;
    int current_level;
    int button_count;
    Button * buttons;
} Game;

Game * initGame(SDL_Surface *screen);

void runGame(Game *game);

void freeGame(Game *game);

void drawGameToSurface(Game *game);

/*
 * Déplace toutes les entités joueur dans la direction spécifiée
 */
void movePlayer(Board *b, Direction dir);
/*
 * Déplace une entité dans la direction spécifiée
 */
Bool moveEntity(Board *b, Entity *box, Direction dir);

// UI
Button * getButtonAtPos(Game *game, int x, int y);

#endif // !GAME_H
