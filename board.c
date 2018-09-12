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
[chrisgraham@mn2svlmtc001sd0 ~]$ ^C
[chrisgraham@mn2svlmtc001sd0 ~]$ cat board.c
#include "board.h"

void display_board (enum color player,
                        enum color intersections[MAX_BOARD][MAX_BOARD])
{
        int i;
        int x;
        int y;

        printf("    X -> ");
        /* Start the grid on a new line and align the spaces */
        printf("\n  ");

        /* Print X values from 1 to Max Board size */
        for (i = 1; i <= MAX_BOARD; i++) {
                printf("%3d", i);
        }
        printf("\n");

        for (y = 0; y < MAX_BOARD; y++) {
                /* Print Y values from 1 to Max Board size */
                printf("%2d", y + 1);
                for (x = 0; x < MAX_BOARD; x++) {
                        /* Print which stone if any occupies the positions */
                        switch (intersections[x][y]) {
                                case EMPTY:
                                        printf("  .");
                                        break;
                                case BLACK:
                                        printf("  B");
                                        break;
                                case WHITE:
                                        printf("  W");
                                        break;
                                default:
                                        /* ERROR */
                                        break;
                        }
                }


                printf ("\n");
        }

        if (player == BLACK) {
                 printf("Black's Turn\n");
        } else {
                printf("White's Turn\n");
        }
}

void get_move(enum color *player,
                enum color M[MAX_BOARD][MAX_BOARD])
{
        int x;
        int y;

        printf("X coordinate: ");
        scanf("%d", &x);
        printf("Y coordinate: ");
        scanf("%d", &y);

        if (M[x - 1][y - 1] == EMPTY) {
                M[x - 1][y - 1] = *player;
                *player = (*player == BLACK ? WHITE : BLACK);
                printf("Position [%d]\n", POS(x,y));
        } else {
                printf("Invalid Move\n");
        }
}

int on_board(int M[MAX_BOARD][MAX_BOARD], int row, int col,
                int visited[MAX_BOARD][MAX_BOARD])
{
        result = (row >= 0) && (row < MAX_BOARD) && (col >= 0) && (col < MAX_BOARD) && (M[row][col] && !visited[row][col]);
        return result;
}

void display_help()
{
        printf("Available Commands\n");
        printf("m - place a stone on the board\n");
        printf("h - Help (this screen)\n");
        printf("q - Quit\n\n");
        printf("Press a key to continue\n");
        getchar();
}

int main ()
{
        char command;
        enum color player = BLACK;
        enum color intersections[MAX_BOARD][MAX_BOARD] = { EMPTY };

        printf("Go Game\n");

        /*
        intersections[0][2] = WHITE;
        intersections[2][2] = BLACK;
        intersections[3][2] = BLACK;
        */

        display_board(player, intersections);

        do {
                printf("Command: ");
                scanf("%c", &command);

                switch (command) {
                        case 'h':
                                display_help();
                                break;
                        case 'm':
                                get_move(&player, intersections);
                                break;
                        default:
                                continue;
                }

                display_board(player, intersections);
        } while (command != 'q');

        return 0;
}
