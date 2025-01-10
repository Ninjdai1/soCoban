#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 1000

int main(int argc, char *argv[])
{
    printf("SoCoban  Copyright (C) 2025  Phantaemon, Ninjdai\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\n\n");
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        fprintf(stderr,"Error while loading SDL :%s\n",
        SDL_GetError());
        return -1 ;
    }
    if(TTF_Init() == -1){
        fprintf(stderr,"Unable to initialize TTF: %s\n",
        TTF_GetError());
        return -1 ;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr,"Unable to initialize IMG: %s\n",
        IMG_GetError());
        return -1 ;
    }

    TTF_Font * police = NULL ;
    police = TTF_OpenFont("fonts/midnight_letters/MidnightLetters.ttf", 30);
    if(police==NULL){
        fprintf(stderr,"Unable to load TTF: %s\n",
        TTF_GetError());
    }

    SDL_Surface * screen = NULL;
    if((screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE))==NULL){
        fprintf(stderr,"Error setting SDL Video Mode: %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    Game * game = initGame(screen, police);

    runGame(game);

    freeGame(game);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    return EXIT_SUCCESS;
}
