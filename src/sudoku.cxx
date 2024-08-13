#include <iostream>
#include <cstring>
using namespace std;

char sudoku[9][9];

void RawMode(bool start) {
    
}

char getch() {
    char ch;
    RawMode(true); 
    ch = getchar();
    RawMode(false);
    return ch;
}

void printSudoku() {
    char key;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            // initial sudoku from input
            key = getch();
            while (!strchr("123456789 ", key)) {
                key = getch(); 
            }
            sudoku[i][j] = key;

            // print in grid
            cout << sudoku[i][j] << ' ';
        }
        cout << '\n';
        if (i % 3 == 2 && i != 8) {
            cout << "------+-------+------\n";
        }
    }
}
int main() {
    // initialize sudoku matrix :3
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = ' ';
        }
    }
    printSudoku();
    getch();
    return 0;

}