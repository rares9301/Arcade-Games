#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <limits>
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
            if (j // abort if solvec
            if (sudoku[i][j] != ' ') {
                continue;
            }
            // init boxes
            for (int k = 0; k < 9; k++) {
                boxes[k] = true;
            }
            // numbers per box
            for (int di = 0; di < 9; di++) {
                if (sudoku[di][j] != ' ') {
                    boxes[(sudoku[di][j] - '0') - 1] = false;
                }
            }
            for (int dj = 0; dj < 9; dj++) {
                if (sudoku[i][dj] != ' ') {
                    boxes[(sudoku[i][dj] - '0') - 1] = false;
                }
            }
            for (int di = i - (i % 3); di < i - (i % 3) + 3; di++) {
                for (int dj = j - (j % 3); dj < j - (j % 3) + 3; dj++) {
                    if (sudoku[di][dj] != ' ') {
                        boxes[(sudoku[di][dj] - '0') - 1] = false;
                    }
                }
            }% 3 == 0 && j != 0) {
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
void scanMatrix() {
    bool solve1, solve2;
    do {
        printSudoku(false);
        try1(solve1);
        try2(solve2);
        usleep(500000); // Sleep for 500ms
    } while (solve1 || solve2);
}

void try1(bool &solve1) {
    solve1 = false;
    bool boxes[9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // if current box is already solved, abort
            if (sudoku[i][j] != ' ') {
                continue;
            }
            // initialize boxes[]
            for (int k = 0; k < 9; k++) {
                boxes[k] = true;
            }
            // keep track of which numbers this box cannot be
            for (int di = 0; di < 9; di++) {
                if (sudoku[di][j] != ' ') {
                    boxes[(sudoku[di][j] - '0') - 1] = false;
                }
            }
            for (int dj = 0; dj < 9; dj++) {
                if (sudoku[i][dj] != ' ') {
                    boxes[(sudoku[i][dj] - '0') - 1] = false;
                }
            }
            for (int di = i - (i % 3); di < i - (i % 3) + 3; di++) {
                for (int dj = j - (j % 3); dj < j - (j % 3) + 3; dj++) {
                    if (sudoku[di][dj] != ' ') {
                        boxes[(sudoku[di][dj] - '0') - 1] = false;
                    }
                }
            }
            int vars = 0;
            char answer;
            for (int k = 0; k < 9; k++) {
                if (boxes[k] == true) {
                    vars++;
                    if (vars > 1) {
                        break;
                    }
                    answer = k + 1 + '0';
                }
            }

            if (vars == 1) {
                sudoku[i][j] = answer;
                solve1 = true;
            }
        }
    }
}

void try2(bool &solve2) {
    solve2 = false;
    int vars;
    int answeri, answerj;
    for (char n = '1'; n <= '9'; n++) {
        for (int i = 0; i < 9; i++) {
            // check boxes
            vars = 0;
            for (int j = 0; j < 9; j++) {
                if (checkBox(i, j, n)) {
                    vars++;
                    if (vars > 1) {
                        break;
                    }
                    answerj = j;
                }
            }
            // box completion
            if (vars == 1) {
                sudoku[i][answerj] = n;
                solve2 = true;
            }
        }
        for (int j = 0; j < 9; j++) {
            // boxes that can be n
            vars = 0;
            for (int i = 0; i < 9; i++) {
                if (checkBox(i, j, n)) {
                    vars++;
                    if (vars > 1) {
                        break;
                    }
                    answeri = i;
                }
            }
            // success
            if (vars == 1) {
                sudoku[answeri][j] = n;
                solve2 = true;
            }
        }
        for (int i = 0; i <= 6; i += 3) {
            for (int j = 0; j <= 6; j += 3) {
                // number of boxes in 3x3 that can be n
                vars = 0;
                for (int di = i; di < i + 3; di++) {
                    for (int dj = j; dj < j + 3; dj++) {
                        if (checkBox(di, dj, n)) {
                            vars++;
                            if (vars > 1) {
                                break;
                            }
                            answeri = di;
                            answerj = dj;
                        }
                    }
                }
                // succes of n
                if (vars == 1) {
                    sudoku[answeri][answerj] = n;
                    solve2 = true;
                }
            }
        }
    }
}

bool checkBox(int i, int j, char n) {
    // TODO: logic for checkBox
    // will search for n on rows and cols then in 3x3 boxes
    return true;
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
    // solve sudoku auto
    scanMatrix();
    cout << "Press any key to continue..." << endl;
    getch();
    return 0;
}