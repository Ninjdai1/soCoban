#include "component.h"
#include "../config.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

void drawComponentToSurface(Component *c, SDL_Surface *screen, TTF_Font *font) {
    SDL_Surface * rectangle = NULL ;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, c->size.x + 8, c->size.y + 8, 32, 0, 0, 0, 0) ;

    SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, c->bg_color.r, c->bg_color.g, c->bg_color.b));
    
    SDL_Rect text_position = {
        .x = c->pos.x,
        .y = c->pos.y
    };

    SDL_Rect rect_position = {
        .x = text_position.x - 4,
        .y = text_position.y - 4
    };
    SDL_BlitSurface(rectangle, NULL, screen, &rect_position);

    if (c->type == TEXT_DISPLAY || c->type == BUTTON) {
        SDL_Surface * text = NULL ;
        text = TTF_RenderText_Blended(font, c->text, c->fg_color);
        SDL_BlitSurface(text, NULL, screen, &text_position);
    }
}

void toggleComponent(Component *b, int show) {
    #if DEBUG
    printf("%s visible: %d -> %d\n", b->id, b->flags.visible, !b->flags.visible);
    #endif /* if DEBUG */
    b->flags.visible = show;
    b->flags.enabled = show;
}
