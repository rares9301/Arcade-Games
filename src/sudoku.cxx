#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
using namespace std;

char sudoku[9][9];

// Used C++ refference for termios.h to come up with this raw reading mode
void RawMode(bool enable) {
  static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt); // old settings
        newt = oldt; // transfer new settings
        newt.c_lflag &= ~(ICANON | ECHO); // disable buffering & echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore 
    }  
}

char getch() {
    char ch;
    RawMode(true); 
    ch = getchar();
    RawMode(false);
    return ch;
}

void printSudoku(bool status) {
    char key;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            // initial sudoku from input
            if (status) {
                key = getch();
                while (!strchr("123456789 ", key)) {
                    key = getch(); 
                }
                sudoku[i][j] = key;
            }
            // print in grid
            cout << sudoku[i][j] << ' ';
        }
        cout << '\n';
        if (i % 3 == 2 && i != 8) {
            cout << "------+-------+------\n";
        }
    }
}

void perform() {
    char key;
    int row, coll;
    printSudoku(false);
    cout << "Enter row and collumn for completion";
    cin >> row >> coll;
    cout << "Enter value:";
    cin >> key;
    cout << "Char entered:" << key << std::flush;
}

int main() {
    // initialize sudoku matrix :3
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = ' ';
        }
    }
    printSudoku(true);
    cout << "[+] Finished reading sudoku matrix!" << endl;
    getch();
    cout << "\033[2J\033[1;1H"; // cls
    perform();
    getch();
    return 0;

}