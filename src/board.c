#include "board.h"
#include "entity.h"
#include "tile.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Bool checkWin(Board *board) {
    int x, y;
    for (x=0; x<board->size.x; x++) {
        for (y=0; y<board->size.y; y++) {
            if (board->static_tiles[x][y] == GOAL_TILE) {
                Entity * e = getEntity(board, x, y);
                if (e==NULL || e->type != BOX_ENTITY_TYPE) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

Entity * getEntity(Board *board, int x, int y) {
    for (int i=0; i<board->entity_count; i++) {
        Entity * e = &board->entities[i];
        if (e->pos.x == x && e->pos.y ==  y) {
            return e;
        }
    }
    return NULL;
}

void printBoardToText(Board *board) {
    int x, y;
    for (y=0; y<board->size.y; y++) {
        for (x=0; x<board->size.x; x++) {
            printf("%c", getTileData(board->static_tiles[x][y]).c);
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
    int x, y;
    int cursor = 0;

    Board * b = malloc(sizeof(Board));
    b->size = getBoardSize(board, length);
    b->entity_count = 0;
    b->static_tiles = malloc(sizeof(Tile *) * b->size.y);

    printVec2d(b->size);

    for (y=0; y<b->size.y; y++) {
        b->static_tiles[y] = malloc(sizeof(Tile) * b->size.x);
        for (x=0; x<=b->size.x; x++) {
            if (board[cursor]=='\n') {
                cursor++;
                for (int t=0; t < (b->size.x-x); t++) {
                    b->static_tiles[y][x+t] = AIR_TILE;
                }
                break;
            }
            Tile t = getTileFromChar(board[cursor]);
            b->static_tiles[y][x] = t;
            if (t == BOX_SPAWN_TILE || t == PLAYER_SPAWN_TILE) {
                b->entity_count += 1;
            }
            cursor++;
        }
    }

    b->entities = malloc(sizeof(Entity) * b->entity_count);
    int cr_ety = 0;
    for (x=0; x<b->size.x; x++) {
        for (y=0; y<b->size.y; y++) {
            EntityType e_type = getEntityTypeFromSpawnTile(b->static_tiles[y][x]);
            if (e_type != INVALID_ENTITY_TYPE) {
                Entity e = {
                    .pos = {x, y},
                    .type = e_type
                };
                b->entities[cr_ety] = e;
                cr_ety++;
            }
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

    fclose(f);
    Board * b = loadBoardFromString(board, length);
    free(board);
    return b;
}

void freeBoard(Board *board){
    for (int i=0; i<board->size.y; i++) {
        free(board->static_tiles[i]);
    }
    free(board->static_tiles);
    free(board->entities);
    free(board);
}

Tile getTileFromChar(char tile_char) {
    switch (tile_char) {
        case '#': return WALL_TILE;
        case 'G': return GOAL_TILE;
        case 'B': return BOX_SPAWN_TILE;
        case 'P': return PLAYER_SPAWN_TILE;
        default: return AIR_TILE;
    }
}
