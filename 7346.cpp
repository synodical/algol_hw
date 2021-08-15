#include <iostream>
using namespace std;
using ll = long long;
const int MAX = 101;
const int INF = 1e9;
const int score[5][5] =
        {{5,-1,-2,-1,-3},
        {-1,5,-3,-2,-4},
        {-2,-3,5,-2,-2},
        {-1,-2,-2,5,-1},
        {-3,-4,-2,-1, -INF}}; //

int t, x_length, y_length;
char Xseq[MAX];
char Yseq[MAX];
int opt[MAX][MAX]; // optimal alignment의 비용 2차원 배열

int tran(char c) {
    switch(c){
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        case '-': return 4;
    }
    return 4;
}

int Max(int a, int b, int c) {
    int t = (a > b) ? a : b;
    return (t > c) ? t : c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> t;
    while (t--) {
        cin >> x_length;
        for (int j = 0; j < x_length; j++) cin >> Xseq[j];
        cin >> y_length;
        for (int j = 0; j < y_length; j++) cin >> Yseq[j];
        
        opt[0][0] = 0;
        
        /* opt init - 틈과 정렬하는 경우 */
        for (int i = 1; i <= x_length; i++) {
            opt[i][0] = opt[i-1][0] + score[ tran(Xseq[i-1]) ][4];
        }
        for (int i = 1; i <= y_length; i++) {
            opt[0][i] = opt[0][i-1] + score[4][ tran(Yseq[i-1]) ];
        }
        
        for (int i = 1; i <= x_length; i++) {
            for (int j = 1; j <= y_length; j++) {
                // case1 == align X[i] with Y[i]
                // case2 == align X[i] with gap
                // case3 == align Y[i] with gap
                int case1 = opt[i-1][j-1] + score[ tran(Xseq[i-1]) ][ tran(Yseq[j-1]) ];
                int case2 = opt[i-1][j]   + score[ tran(Xseq[i-1]) ][4];
                int case3 = opt[i][j-1]   + score[4][ tran(Yseq[j-1]) ];
                opt[i][j] = Max(case1, case2, case3);
            }
        }
        cout << opt[x_length][y_length] << '\n';
    }
    return 0;
}
