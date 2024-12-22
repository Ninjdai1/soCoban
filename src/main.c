#pragma GCC diagnostic ignored "-Wswitch"

#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <stdio.h>
#include "board.h"
#include "game.h"

#define WIDTH 1000
#define HEIGHT 1000

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        fprintf(stderr,"Error while loading SDL :%s\n",
        SDL_GetError());
        return -1 ;
    }

    Board * b = loadBoardFromFile("level1.scb");

    printBoardToText(b);

    SDL_Surface * screen = NULL;
    if((screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE))==NULL){
        fprintf(stderr,"Error setting SDL Video Mode: %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    drawBoardToSurface(b, screen);

    int cont=1;
    SDL_Event event;
    while (cont) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                cont=0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case 'q':
                        cont=0;
                        break;
                }
                printf("Keydown\n");
                break;
        }
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
