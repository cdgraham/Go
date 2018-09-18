#include "board.h"

void display_board (enum color player, enum color intersections[MAX_BOARD][MAX_BOARD]) {
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

int on_board(enum color player, enum color M[MAX_BOARD][MAX_BOARD], int row, int col,
                bool visited[MAX_BOARD][MAX_BOARD])
{
        return  (row >= 0) && (row < MAX_BOARD) && 
		(col >= 0) && (col < MAX_BOARD) && 
		(M[row][col] == player && !visited[row][col]);
}

void DFS(enum color player, enum color M[][MAX_BOARD], int row, int col, bool visited[][MAX_BOARD])
{
	// These arrays are used to get row and column numbers of 4 neighbors of given cell
	static int row_num[] = {-1, 0, 0, 1};
	static int col_num[] = {0, 1, -1, 0};

	// Mark this cell as visited
	visited[row][col] = true;
	
	// Recursion for all connected neighbors
	for (int k = 0; k < 4; k++)
	{
		printf("checking [%d][%d] ", row + row_num[k], col + col_num[k]);
		if (on_board(player, M, row + row_num[k], col + col_num[k], visited))
		{
			printf(" is on board\n");
			DFS(player, M, row + row_num[k], col + col_num[k], visited);
		}
	}
}

int count_islands(enum color player, enum color M[][MAX_BOARD])
{
	int i, j;
	bool visited[MAX_BOARD][MAX_BOARD];
	memset(visited, 0, sizeof(visited));

	// Initialize count to 0 and travese all cells
	int count = 0;
	for (i = 0; i < MAX_BOARD; ++i)
		for (j = 0; j < MAX_BOARD; ++j)
			if (M[i][j] == player && !visited[i][j])
			{
				printf("Visited [%d][%d]\n", i, j);
				DFS(player, M, i, j, visited);
				++count;
			}

	return count;
}

void display_help()
{
        printf("Available Commands\n");
        printf("m - place a stone on the board\n");
        printf("c - count longest chain on the board\n");
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

        printf("Go Game\n\n");

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
                        case 'c':
                                printf("Longest chain is %d\n", count_islands(player, intersections));
                                break;
                        default:
                                continue;
                }

                display_board(player, intersections);
        } while (command != 'q');

        return 0;
}
