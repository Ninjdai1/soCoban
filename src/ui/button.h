#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "../board.h"

typedef struct ButtonFlags_I {
    uint8_t visible:1;
    uint8_t refreshAfterCallback:1;
} ButtonFlags;

typedef struct Button_I {
    char * id;
    char * name;
    void (*callback)(Board*);
    Vec2D pos;
    Vec2D size;
    ButtonFlags flags;
} Button;

void drawButtonToSurface(Button *b, SDL_Surface *screen);

#endif // !UI_BUTTON_H
