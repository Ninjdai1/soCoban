#include "tile.h"

TileData getTileData(Tile t){
    if (t >= MAX_TILE) return TILES[AIR_TILE];
    return TILES[t];
};
