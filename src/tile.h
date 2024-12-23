#ifndef TILE_H
#define TILE_H

#include "utils.h"

typedef struct TileData_I {
    char c;
    Color col;
    Bool collision;
} TileData;

typedef enum Tile_E {
    INVALID_TILE = -1,
    AIR_TILE,
    WALL_TILE,
    GOAL_TILE,
    BOX_SPAWN_TILE,
    PLAYER_SPAWN_TILE,
    MAX_TILE
} Tile;

static const TileData TILES[MAX_TILE] = {
    {' ', {0, 0, 0}, FALSE},
    {'#', {255, 255, 255}, TRUE},
    {'G', {0, 255, 0}, FALSE},
    {'B', {0, 0, 0}, FALSE},
    {'P', {0, 0, 0}, FALSE},
};

TileData getTileData(Tile t);

#endif // !TILE_H
