#include "component.h"
#include "../config.h"
#include <SDL/SDL_ttf.h>
#include <stdio.h>

void drawComponentToSurface(Component *b, SDL_Surface *screen, TTF_Font *font) {
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

void toggleComponent(Component *b) {
    #if DEBUG
    printf("%s visible: %d -> %d\n", b->id, b->flags.visible, !b->flags.visible);
    #endif /* if DEBUG */
    b->flags.visible = !b->flags.visible;
    b->flags.enabled = !b->flags.enabled;
}
