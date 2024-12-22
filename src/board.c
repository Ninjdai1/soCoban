#include "board.h"
#include "tile.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void printBoardToText(Board *board) {
    int x, y;
    for (y=0; y<board->size.y; y++) {
        for (x=0; x<board->size.x; x++) {
            printf("%c", board->data[y][x]);
        }
        printf("\n");
    }
}

Vec2D getBoardSize(char *board, int length) {
    int cursor = 0;
    Vec2D size = {
        .x = 0,
        .y = 0,
    };
    for (int i=0; i < length; i++) if (board[i]=='\n') size.y++;

    for (int line=0; line < size.y; line++) {
        int line_w = 0;
        while (board[cursor + line_w]!='\n') line_w++;

        for (int i=1; i <= (length - cursor); i++){
            cursor++;
            if (board[cursor]=='\n') {
                if (i > size.x) size.x = i;
                cursor++;
                break;
            }
        }
    }

    return size;
}

Board * loadBoardFromString(char *board, int length){
    if (board == NULL) {
        printf("Invalid board string\n");
        return NULL;
    }
    int x;
    int cursor = 0;

    Board * b = malloc(sizeof(Board));
    b->size = getBoardSize(board, length);
    b->data = malloc(sizeof(Tile *) * b->size.y);

    printVec2d(b->size);

    for (int y=0; y<b->size.y; y++) {
        b->data[y] = malloc(sizeof(Tile) * b->size.x);
        for (x=0; x<=b->size.x; x++) {
            if (board[cursor]=='\n') {
                cursor++;
                for (int t=0; t < (b->size.x-x); t++) {
                    b->data[y][x+t] = AIR_TILE;
                }
                break;
            }
            b->data[y][x] = getTile(board[cursor]);
            cursor++;
        }
    }

    return b;
}

/*
 * Loads a board from input file
*/
Board * loadBoardFromFile(char *file){
    FILE * f = fopen(file, "r");
    if (f==NULL) {
        perror("Error opening board file");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char * board = malloc(sizeof(char)*length);
    fread(board, 1, length, f);
    return loadBoardFromString(board, length);
}

void freeBoard(Board *board){
    for (int i=0; i<board->size.y; i++) {
        free(board->data[i]);
    }
    free(board->data);
    free(board);
}

Tile getTile(char tile_char) {
    switch (tile_char) {
        case '#': return WALL_TILE;
        case 'G': return GOAL_TILE;
        case 'B': return BOX_SPAWN_TILE;
        case 'P': return PLAYER_SPAWN_TILE;
        default: return AIR_TILE;
    }
}
