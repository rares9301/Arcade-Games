#include <stdio.h>
#include <stdlib.h>

char board[3][3];

int main() {
    int player = 0;
    int row, col;
    char mark;
    initializeBoard(board);
    while (1) {
        drawBoard(board);
        if (player % 2 == 0) {
            mark = 'X';
        } else {
            mark = 'O';
        }
        do {
            printf("Player %d, enter a row and column: ", player + 1);
            scanf("%d %d", &row, &col);
        } while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != '*');
        markBoard(board, row, col, mark);
        if (checkWin(board)) {
            printf("Player %c wins!\n", (player + 1) % 2 ? 'X' : 'O');
            break;
        }
        player++;
    }
    return 0;
}
