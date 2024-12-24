#include "button.h"
#include <SDL/SDL_ttf.h>

void drawButtonToSurface(Button *b, SDL_Surface *screen, TTF_Font *font) {
    SDL_Surface * rectangle = NULL ;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, b->size.x + 8, b->size.y + 8, 32, 0, 0, 0, 0) ;

    SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 120, 0, 0));

    SDL_Color cBlanc= {205,205,205};
    SDL_Surface * text = NULL ;
    text = TTF_RenderText_Blended(font, b->name, cBlanc);

    
    SDL_Rect text_position = {
        .x = b->pos.x,
        .y = b->pos.y
    };
    
    SDL_Rect rect_position = {
        .x = text_position.x - 4,
        .y = text_position.y - 4
    };

    SDL_BlitSurface(rectangle, NULL, screen, &rect_position);
    SDL_BlitSurface(text, NULL, screen, &text_position);
}
