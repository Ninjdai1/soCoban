#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "../board.h"
#include <SDL/SDL_ttf.h>

typedef struct Game_I Game; //Déclaration pour éviter les #include recursifs

typedef struct ButtonFlags_I {
    uint8_t visible:1;
    uint8_t enabled:1;
    uint8_t refreshAfterCallback:1;
} ButtonFlags;

typedef struct Button_I {
    char * id;
    char * name;
    void (*callback)(Game*);
    Vec2D pos;
    Vec2D size;
    ButtonFlags flags;
} Button;

void drawButtonToSurface(Button *b, SDL_Surface *screen, TTF_Font *font);

#endif // !UI_BUTTON_H
