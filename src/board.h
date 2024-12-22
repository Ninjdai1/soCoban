#ifndef BOARD_H
#define BOARD_H

#include "utils.h"
#include "tile.h"

/*
 * \brief Representation of a Sokoban board
 */
typedef struct Board_I {
    Vec2D size;
    Tile ** data; /**<  Tiles of the board*/
} Board;

/*
 * Load a tile board from a string.
 * Board is represented in the string as multiple lines separated by a \n.
 * Air: ' '; Wall: '#'; Goal: 'G'; PlayerSpawn: 'P'; BoxSpawn: 'B';
 */
Board * loadBoardFromString(char *board, int length);
Board * loadBoardFromFile(char *file);

void printBoardToText(Board *board);

void freeBoard(Board *board);

/*
 * Get the tile that corresponds to title_char.
 * \note If no corresponding tile is found, returns Air.
 */
Tile getTile(char tile_char);

#endif // !BOARD_H
