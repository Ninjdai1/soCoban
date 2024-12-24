#include "board.h"
#include "game.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 1000

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        fprintf(stderr,"Error while loading SDL :%s\n",
        SDL_GetError());
        return -1 ;
    }

    SDL_Surface * screen = NULL;
    if((screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE))==NULL){
        fprintf(stderr,"Error setting SDL Video Mode: %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    Game * game = initGame(screen);
    printBoardToText(game->board);

    runGame(game);

    freeGame(game);
    SDL_Quit();
    return EXIT_SUCCESS;
}
