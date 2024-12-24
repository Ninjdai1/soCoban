#ifndef ENTITY_H
#define ENTITY_H

#include "tile.h"
#include "utils.h"

/*
 * Metadonnées d'une entité
 */
typedef struct EntityData_I {
    Color color; /**< Couleur d'affichage de l'entité*/ // TEMPORAIRE: SYSTÈME DE SPRITES ET IMAGES
} EntityData;

/*
 * Types d'entités
 */
typedef enum EntityType_E {
    INVALID_ENTITY_TYPE = -1,
    PLAYER_ENTITY_TYPE, /**< Une entité contrôllée par le joueur*/
    BOX_ENTITY_TYPE     /**< Une entité devant être déplacée sur un Goal*/
} EntityType;

/*
 * Instance d'une entité
 */
typedef struct Entity_I {
    EntityType type;/**< Le type d'entité*/
    Vec2D pos;/**< La position actuelle de l'entité*/
} Entity;

static const EntityData ENTITY_DATA[BOX_ENTITY_TYPE+1] = {
    {/*Player*/
        .color = {255, 255, 0}
    },
    {/*Boxes*/
        .color = {122, 53, 17}
    },
};

/*
 * Renvoie le type d'entité correspondant à une Tile d'apparition
 */
EntityType getEntityTypeFromSpawnTile(Tile tile);

#endif // !ENTITY_H
