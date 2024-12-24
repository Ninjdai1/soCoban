#include "utils.h"
#include <SDL/SDL_keysym.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wswitch"

#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <stdio.h>
#include "board.h"
#include "game.h"

#define WIDTH 1000
#define HEIGHT 1000

#define MAX_LEVEL 3

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        fprintf(stderr,"Error while loading SDL :%s\n",
        SDL_GetError());
        return -1 ;
    }

    int level = 1;
    char level_path[28];
    sprintf(level_path, "levels/level%d.scb", level);
    Board * board = loadBoardFromFile(level_path);

    printBoardToText(board);

    SDL_Surface * screen = NULL;
    if((screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE))==NULL){
        fprintf(stderr,"Error setting SDL Video Mode: %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    drawBoardToSurface(board, screen);

    int cont=1;
    int draw = 0;
    SDL_Event event;
    while (cont) {
        draw = 0;
        //SDL_PollEvent(&event);
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
                    case 'r':
                        initEntities(board);
                        draw = 1;
                        break;
                    case SDLK_UP:
                        movePlayer(board, DIRECTION_UP);
                        draw = 1;
                        break;
                    case SDLK_DOWN:
                        movePlayer(board, DIRECTION_DOWN);
                        draw = 1;
                        break;
                    case SDLK_RIGHT:
                        movePlayer(board, DIRECTION_RIGHT);
                        draw = 1;
                        break;
                    case SDLK_LEFT:
                        movePlayer(board, DIRECTION_LEFT);
                        draw = 1;
                        break;
                }
                break;
        }
        if (checkWin(board)) {
            printf("Victoire ! Niveau %d terminé !\n", level);
            if (level < MAX_LEVEL) {
                level++;
                sprintf(level_path, "levels/level%d.scb", level);
                freeBoard(board);
                board = loadBoardFromFile(level_path);
                draw = 1;
            } else {
                printf("Jeu terminé ! Félicitations");
                cont = 0;
            }
        }
        if (draw==1) {
            drawBoardToSurface(board, screen);
        }
    }
    freeBoard(board);
    SDL_Quit();
    return EXIT_SUCCESS;
}
