#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdio.h>

#define MAX_BOARD       9       /* Maximum board size */

#define POS(i,j)        ((MAX_BOARD * (j - 1)) + (i - 1))
#define NORTH(pos)      ((pos) - MAX_BOARD)
#define SOUTH(pos)      ((pos) + MAX_BOARD)
#define EAST(pos)       ((pos) + 1)
#define WEST(pos)       ((pos) - 1)


enum color {
        EMPTY,
        BLACK,
        WHITE
};

struct chain {
        int color;
        int origin;
        int size;
        int liberties;
};

/* Functions */
void display_board (enum color player,
                        enum color intersections[MAX_BOARD][MAX_BOARD]);
void display_help ();
void get_move (enum color *player,
                enum color intersections[MAX_BOARD][MAX_BOARD]);
int on_board(int M[MAX_BOARD][MAX_BOARD], int row, int col,
                int visited[MAX_BOARD][MAX_BOARD])

#endif  /* _BOARD_H_ */
