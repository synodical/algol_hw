#include <iostream>
#include <fstream>
using namespace std;

int sudoku[9][9];
int ans[9][9];
bool row[9][9+1];
bool column[9][9+1];
bool square[9][9+1];
ifstream ifile;
int testcase;
int not_zero = 0;
bool flag = false;

void init() {
    not_zero = 0;
    flag = false;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            sudoku[i][j] = 0;
            row[i][j] = false;
            column[i][j] = false;
            square[i][j] = false;
        }
    }
}

inline int sq_index(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

void input() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ifile >> sudoku[i][j];
            if (sudoku[i][j] != 0) {
                not_zero++;
                row[i][ sudoku[i][j] ] = true;
                column[j][ sudoku[i][j] ] = true;
                square[ sq_index(i, j) ][ sudoku[i][j] ] = true;
            }
        }
    }
}

void print_ans() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << '\n';
    }
    return;
}

void backtracking(int cnt) {

    if(cnt == 81) {
        print_ans();
        return;
    }
    int x = cnt / 9;
    int y = cnt % 9;
    
    if(sudoku[x][y] == 0) {
        for (int i = 1; i <= 9; i++) {
            if(!row[x][i] && !column[y][i] && !square[sq_index(x, y)][i]) { // promising
                row[x][i] = true;
                column[y][i] = true;
                square[sq_index(x, y)][i] = true;
                sudoku[x][y] = i;
                
                backtracking(cnt + 1);
                
                row[x][i] = false; // backtracking
                column[y][i] = false;
                square[sq_index(x, y)][i] = false;
                sudoku[x][y] = 0;
            }
        }
    }
    else {
        backtracking(cnt + 1);
    }
}

int main() {
    ifile.open("input.txt"); 
    if(ifile.is_open()) {
        ifile >> testcase;
        for (int t = 1; t <= testcase; t++) {
            cout << "sudoku " << t << '\n';
            init();
            input();
            backtracking(0);
        }
    }
    return 0;
}

