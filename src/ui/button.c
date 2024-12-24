#include "button.h"

void drawButtonToSurface(Button *b, SDL_Surface *screen) {
    SDL_Surface * rectangle = NULL ;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, b->size.x, b->size.y, 32, 0, 0, 0, 0) ;

    SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 120, 120, 120));

    SDL_Rect position = {
        .x = b->pos.x,
        .y = b->pos.y
    };
    SDL_BlitSurface(rectangle, NULL, screen, &position);
}
