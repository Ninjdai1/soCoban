#ifndef TILE_H
#define TILE_H

#include "utils.h"

/**
 * Métadonnées d'une Tile
 */
typedef struct TileData_I {
    char c;         /**< Charactère de représentation de la tuile*/
    Color col;      /**< Couleur d'affichage de la Tile*/ //TEMPORAIRE: SYSTÈME DE SPRITES ET IMAGES
    Bool collision; /**< La Tile a-t-elle des collisions*/
} TileData;

/**
 * Types de Tiles
 * Les Tiles n'ayant pas de données, on utilise un enum, dont les valeurs correspondent à un entier, pour limiter l'utilisation de mémoire avec des instances multiples de struct similaires dans les Board
 */
typedef enum Tile_E {
    INVALID_TILE = -1,
    AIR_TILE,           /**< Air*/
    WALL_TILE,          /**< Mur*/
    FLOOR_TILE,         /**< Sol*/
    GOAL_TILE,          /**< Objectif*/
    BOX_SPAWN_TILE,     /**< Apparition de Box*/
    PLAYER_SPAWN_TILE,  /**< Apparition de Player*/
    GOAL_BOX_SPAWN_TILE,/**< Apparition de Box ET Objectif*/
    MAX_TILE // Utilisée pour la taille d'array de TILES
} Tile;

static const TileData TILES[MAX_TILE] = {
    {' ', {0, 0, 0}, FALSE},
    {'#', {255, 255, 255}, TRUE},
    {'_', {0, 0, 0}, FALSE},
    {'G', {0, 255, 0}, FALSE},
    {'B', {0, 0, 0}, FALSE},
    {'P', {0, 0, 0}, FALSE},
    {'g', {0, 255, 0}, FALSE},
};

/**
 * Renvoie les métadonnées de la Tile correspondante
 */
TileData getTileData(Tile t);

/**
 * Renvoie un booléan indiquant si la Tile passée est une Tile d'Objectif
 * Utilisée car des Tiles peuvent être des Tiles d'Objectif ET d'Apparition
 */
Bool isGoalTile(Tile t);
/**
 * Renvoie un booléan indiquant si la Tile passée est une Tile d'Apparition
 * Utilisée car des Tiles peuvent être des Tiles d'Apparition ET d'Objectif
 */
Bool isSpawnerTile(Tile t);

#endif // !TILE_H
