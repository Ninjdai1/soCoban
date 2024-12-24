#ifndef UTILS_H
#define UTILS_H

/*
 * Représentation d'un booléen pour faciliter la compréhension des types de retour des fonctions s'en servant
 */
typedef enum Bool_E {
    TRUE = 1,
    FALSE = 0
} Bool;

/*
 * Directions
 */
typedef enum Direction_E {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_RIGHT,
    DIRECTION_LEFT
} Direction;

/*
 * Vecteur contenant deux éléments, utilisé pour représenter des coordonnées ou dimensions
 */
typedef struct Vec2D_I {
    int x;
    int y;
} Vec2D;

/*
 * Affiche un Vec2D dans la sortie standart
 */
void printVec2d(Vec2D vec);

/*
 * Couleur, utilisée pour l'affichage des Tiles et Entities
 */
typedef struct Color_I {
    int r;
    int g;
    int b;
} Color;

/*
 * Renvoie un Vec2D correspondant à la direction passée en paramètre
 */
Vec2D getVecFromDirection(Direction dir);

/*
 * Renvoie la somme des deux vecteurs passés en paramètre
 */
Vec2D vecSum(Vec2D vec1, Vec2D vec2);

#endif // !UTILS_H
