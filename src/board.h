#ifndef BOARD_H
#define BOARD_H

#include "entity.h"
#include "utils.h"
#include "tile.h"
#include <SDL/SDL_video.h>

/*
 * Representation d'un plateau de jeu
 */
typedef struct Board_I {
    Vec2D size;             /**< Vecteur représentant les dimensions du plateau*/
    Tile ** static_tiles;   /**< Matrice des tuiles du plateau*/
    int entity_count;       /**< Nombre d'entités sur le plateau*/
    Entity * entities;      /**< Liste des `entity_count` entités du plateau*/
} Board;

/*
 * Renvoie un plateau généré à partir d'un string
 * Le plateau est représenté dans le string comme plusieurs lignes séparées par un \n.
 * Air: ' '; Wall: '#'; Goal: 'G'; PlayerSpawn: 'P'; BoxSpawn: 'B', Goal AND BoxSpawn: 'g';
 */
Board * loadBoardFromString(char *board, int length);
/*
 * Renvoie le plateau généré à partir du texte contenu dans `file`!
 */
Board * loadBoardFromFile(char *file);

/*
 * Initialise les entités du plateau passé en paramètre
 * Peut être utilisé pour réinitialiser l'état du plateau
 */
void initEntities(Board *board);

/*
 * Affiche le plateau sous format texte dans la sortie standart
 */
void printBoardToText(Board *board);

/*
 * Dessine le `board` sur le `screen`
 */
void drawBoardToSurface(Board *b, SDL_Surface * screen);

/*
 * Libère la mémoire utilisée par le plateau
 */
void freeBoard(Board *board);

/*
 * Renvoie la Tile correspondant au caractère passé en paramètre
 * \note Renvoie Air si le caractère est invalide.
 */
Tile getTileFromChar(char tile_char);

/*
 * Renvoie TRUE si toutes les boites sont sur les Goal, FALSE sinon
 */
Bool checkWin(Board *board);

/*
 * Renvoie un pointeur sur l'Entity à la position spécifiée
 * Renvoie NULL si aucune Entity n'est à cette position
 */
Entity * getEntity(Board *board, int x, int y);
/*
 * Renvoie la Tile à la position spécifiée
 */
Tile getTile(Board *board, int x, int y);
/*
 * Remplace la Tile à la position spécifiée
 */
void setTile(Board *board, int x, int y, Tile t);

#endif // !BOARD_H
