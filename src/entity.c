#include "entity.h"
#include "tile.h"

EntityType getEntityTypeFromSpawnTile(Tile tile) {
    switch (tile) {
        case PLAYER_SPAWN_TILE:
            return PLAYER_ENTITY_TYPE;
        case BOX_SPAWN_TILE:
            return BOX_ENTITY_TYPE;
        case GOAL_BOX_SPAWN_TILE:
            return BOX_ENTITY_TYPE;
        default:
            return INVALID_ENTITY_TYPE;
    }
}
