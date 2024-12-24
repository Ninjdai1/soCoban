#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "utils.h"
#include <SDL/SDL_video.h>

/*
 * Dessine le `board` sur le `screen`
 */
void drawBoardToSurface(Board *b, SDL_Surface * screen);

/*
 * Déplace toutes les entités joueur dans la direction spécifiée
 */
void movePlayer(Board *b, Direction dir);
/*
 * Déplace une entité dans la direction spécifiée
 */
Bool moveEntity(Board *b, Entity *box, Direction dir);

#endif // !GAME_H
