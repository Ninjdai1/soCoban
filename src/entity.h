#ifndef ENTITY_H
#define ENTITY_H

#include "tile.h"
#include "utils.h"

typedef struct EntityData_I {
    Color color;
} EntityData;

typedef enum EntityType_E {
    INVALID_ENTITY_TYPE = -1,
    PLAYER_ENTITY_TYPE,
    BOX_ENTITY_TYPE,
    MAX_ENTITY_TYPE
} EntityType;

typedef struct Entity_I {
    EntityType type;
    Vec2D pos;
} Entity;

static const EntityData ENTITY_DATA[MAX_ENTITY_TYPE] = {
    {/*Player*/
        .color = {255, 255, 0}
    },
    {/*Boxes*/
        .color = {122, 53, 17}
    },
};

EntityType getEntityTypeFromSpawnTile(Tile tile);

#endif // !ENTITY_H
