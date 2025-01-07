#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "../board.h"
#include <SDL/SDL_ttf.h>

typedef struct Game_I Game; //Déclaration pour éviter les #include recursifs

/**
 * Type de Component, utilisé pour les différencier tout en utilisant une structure commune
 */
typedef enum ComponentType_E {
    TEXT_DISPLAY,
    BUTTON
} ComponentType;

/*
 * Dans l'ordre de dessin, à quelle priorité dessiner le Component
 */
typedef enum DrawPriority_E {
    FIRST,
    NONE,
    LAST
} DrawPriority;

/**
 * Données de Component
 * Utilisées via des Bits d'entier non signé pour limiter l'utilisation de mémoire
 */
typedef struct ComponentFlags_I {
    uint8_t visible:1;              /**< Le Component est-il visible*/
    uint8_t enabled:1;              /**< Le Component est-il activé (si non, les clics dessus n'auront par exemple pas d'effet)*/
    uint8_t refreshAfterCallback:1; /**< Après l'activation d'une fonction attachée au Component, doit-on redessiner le Board*/
} ComponentFlags;

/**
 * Structure principale d'un Component
 */
typedef struct Component_I {
    ComponentType type;         /**< Type du Component*/
    char * id;                  /**< ID du component: string unique pour l'identifier facilement*/
    char * text;                /**< Texte du Component: string utilisé lors de l'affichage*/
    void (*callback)(Game*);    /**< Callback: pointeur de fonction appelée lors de l'activation du Component (par exemple via un clic)*/
    Vec2D pos;                  /**< Position du Component sur l'écran*/
    Vec2D size;                 /**< Dimensions du Component*/
    ComponentFlags flags;       /**< Données additionnelles du Component*/
    SDL_Color fg_color;         /**< Couleur d'avant-plan du Component*/
    SDL_Color bg_color;         /**< Couleur d'arrière-plan du Component*/
    DrawPriority priority;      /**< À quelle priorité dessiner le Component*/
} Component;

/**
* Macro des valeurs par défaut d'un Component
* utilisée lors de l'initialisation d'un Component avec une structure par points
*/
#define DEFAULT_COMPONENT_INITIALIZERS .bg_color = getDefaultColor(COLOR_GREY), .fg_color = getDefaultColor(COLOR_WHITE), .priority = NONE

/**
 * Dessine un Component
 */
void drawComponentToSurface(Component *b, SDL_Surface *screen, TTF_Font *font);

/**
 * Active/Désactive la visibilité et fonctionnalité de clic d'un Component selon le paramètre "show": 0 ou 1
 * Principalement utilisé pour des éléments interactifs tels que BUTTON
 */
void toggleComponent(Component *b, int show);

#endif // !UI_BUTTON_H
