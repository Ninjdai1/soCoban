#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "../board.h"
#include <SDL/SDL_ttf.h>

typedef struct Game_I Game; //Déclaration pour éviter les #include recursifs

typedef enum ComponentType_E {
    TEXT_DISPLAY,
    BUTTON
} ComponentType;

typedef struct ComponentFlags_I {
    uint8_t visible:1;
    uint8_t enabled:1;
    uint8_t refreshAfterCallback:1;
} ComponentFlags;

typedef struct Component_I {
    ComponentType type;
    char * id;
    char * name;
    void (*callback)(Game*);
    Vec2D pos;
    Vec2D size;
    ComponentFlags flags;
} Component;

void drawComponentToSurface(Component *b, SDL_Surface *screen, TTF_Font *font);
void toggleComponent(Component *b);

#endif // !UI_BUTTON_H
