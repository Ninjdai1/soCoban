#include "tile.h"
#include "utils.h"

TileData getTileData(Tile t){
    if (t >= MAX_TILE) return TILES[AIR_TILE];
    return TILES[t];
};

Bool isGoalTile(Tile t) {
    if (t == GOAL_TILE || t == GOAL_BOX_SPAWN_TILE) {
        return TRUE;
    }
    return FALSE;
}

Bool isSpawnerTile(Tile t){
    if (t == BOX_SPAWN_TILE || t == PLAYER_SPAWN_TILE || t == GOAL_BOX_SPAWN_TILE) {
        return TRUE;
    }
    return FALSE;
}
