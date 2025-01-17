#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "utils.h"
#include "ui/component.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_video.h>
#include <stdint.h>

#define MAX_LEVEL 4

typedef struct GameFlags_I {
    uint32_t running:1;
    uint32_t paused:1;
    uint32_t draw:1;
    uint32_t clear:1;
} GameFlags;

typedef struct Game_I {
    SDL_Surface * screen;
    TTF_Font * game_font;
    Board * board;
    GameFlags flags;
    int current_level;
    int button_count;
    Component * components;
    int score[MAX_LEVEL];
} Game;

/**
 * Initialise le jeu avec le plateau, l'interface utilisateur...
 */
Game * initGame(SDL_Surface *screen, TTF_Font *game_font);

/**
 * Lance la boucle principale du jeu
 */
void runGame(Game *game);

/**
 * Libère l'espace mémoire utilisé par la structure Game et ses membres
 */
void freeGame(Game *game);

/**
 * Appelle les différentes fonctions d'affichage du plateau et de l'interface utilisateur
 */
void drawGameToSurface(Game *game);

/**
 * Réinitialise le jeu au début du niveau actuel
 */
void resetGameBoard(Game *game);

/**
 * Déplace toutes les entités joueur dans la direction spécifiée
 */
void movePlayer(Game *g, Direction dir);

/**
 * Déplace une entité dans la direction spécifiée
 */
Bool moveEntity(Board *b, Entity *box, Direction dir);

// UI
/**
 * Renvoie le premier bouton situé aux coordonnées spécifiées
 */
Component * getButtonAtPos(Game *game, int x, int y);

#endif // !GAME_H
