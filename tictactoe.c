#include <stdio.h>
#include <stdlib.h>

char board[3][3];

void initializeBoard(char (*board)[3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = '*';
        }
    }
}

void drawBoard(char (*board)[3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void markBoard(char (*board)[3], int row, int col, char mark) {
    board[row][col] = mark;
}

int checkWin(char (*board)[3]) {
    int i;
    for (i = 0; i < 3; i++) {
        if (board[i][0] != '*' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] != '*' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    if (board[0][0] != '*' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] != '*' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

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
