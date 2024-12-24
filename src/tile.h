#ifndef TILE_H
#define TILE_H

#include "utils.h"

/*
 * Métadonnées d'une Tile
 */
typedef struct TileData_I {
    char c;         /**< Charactère de représentation de la tuile*/
    Color col;      /**< Couleur d'affichage de la Tile*/ //TEMPORAIRE: SYSTÈME DE SPRITES ET IMAGES
    Bool collision; /**< La Tile a-t-elle des collisions*/
} TileData;

/*
 * Types de Tiles
 * Les Tiles n'ayant pas de données, on utilise un enum, dont les valeurs correspondent à un entier, pour limiter l'utilisation de mémoire avec des instances multiples de struct similaires dans les Board
 */
typedef enum Tile_E {
    INVALID_TILE = -1,
    AIR_TILE,           /**< Air*/
    WALL_TILE,          /**< Mur*/
    GOAL_TILE,          /**< Objectif*/
    BOX_SPAWN_TILE,     /**< Apparition de Box*/
    PLAYER_SPAWN_TILE,  /**< Apparition de Player*/
    MAX_TILE // Utilisée pour la taille d'array de TILES
} Tile;

static const TileData TILES[MAX_TILE] = {
    {' ', {0, 0, 0}, FALSE},
    {'#', {255, 255, 255}, TRUE},
    {'G', {0, 255, 0}, FALSE},
    {'B', {0, 0, 0}, FALSE},
    {'P', {0, 0, 0}, FALSE},
};

/*
 * Renvoie les métadonnées de la Tile correspondante
 */
TileData getTileData(Tile t);

#endif // !TILE_H
