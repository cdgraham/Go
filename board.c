#include "board.h"

struct chain {
        int color;
        int origin;
        int size;
        int liberties;
};

int main () {
        int x;
        int y;

        enum color points[MAX_BOARD][MAX_BOARD] = { EMPTY };

        printf("Go Game\n");

        points[0][2] = WHITE;
        points[2][2] = BLACK;
        points[3][2] = BLACK;

       for (x = 0; x < MAX_BOARD; x++) {
                for (y = 0; y < MAX_BOARD; y++) {
                        if (points[x][y] == EMPTY) {
                                printf(" .");
                        } else if (points[x][y] == BLACK) {
                                printf(" B");
                        } else if (points[x][y] == WHITE) {
                                printf(" W");
                        } else {
                                /* ERROR */
                                return -1;
                        }
                }
                printf ("\n");
        }

        return 0;
}
