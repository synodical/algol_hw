#include <iostream>
#include <fstream>
#include <algorithm> // min 함수
#define MAX 102
#define gap 3
#define mismatch 2
using namespace std;

int m, n;
char Xseq[MAX];
char Yseq[MAX];
int O[MAX][MAX]; // optimal alignment의 비용 2차원 배열
int P[MAX][MAX]; // O를 min에서 선택하게된 case를 기억하는 배열
char align_ans[MAX][MAX]; // Xseq, Yseq가 적절한 '-'이 삽입되어 정렬된 2차원 배열

int min(int a, int b, int c) {
     return (a <= b && a <= c) ? a :        // if      (a < b && a < c) return a;
            (b <= a && b <= c) ? b : c;
}
void opt() {
    int penalty;
    for (int i = 0; i <= m; i++) {
        O[i][0] = gap * i;
    }
    for (int j = 0; j <= n; j++) {
        O[0][j] = gap * j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            /* penalty를 조건에 따라 다르게 저장 */
            if(Xseq[i] == Yseq[j]) penalty = 0;
            else if(Xseq[i] == '-' || Yseq[j] == '-') penalty = gap;
            else penalty = mismatch;
            
            int c1 = O[i-1][j-1] + penalty;
            int c2 = O[i-1][j] + gap;
            int c3 = O[i][j-1] + gap;
            O[i][j] = min( c1, c2, c3 );
            
            if(c1 == min( c1, c2, c3 )) P[i][j] = 1;
            if(c2 == min( c1, c2, c3 )) P[i][j] = 2;
            if(c3 == min( c1, c2, c3 )) P[i][j] = 3;
        }
    }
}
/* 재귀로 case를 역추적해서 input된 dna 데이터 정렬함 */
void align(int x, int y) {
    int loc = x;
    if(x == m && y == n) loc = (x > y) ? x : y; // align_ans의 크기는 얼마인가?
    
    if(P[x][y] == 1) { // align X[x] and Y[y]
        align_ans[1][loc] = Xseq[x];
        align_ans[2][loc] = Yseq[y];
        align(x - 1, y - 1);
    }
    if(P[x][y] == 2) { // align X[x] and gap
        align_ans[1][x] = Xseq[x];
        align_ans[2][x] = '-';
        align(x - 1, y);
    }
    if(P[x][y] == 3) { // align gap and Y[y]
        align_ans[1][y] = '-';
        align_ans[2][y] = Yseq[y];
        align(x, y - 1);
    }
}
/* 배열을 iflie로 읽어들이기 전 모두 '-'으로 초기화 */
void init_seq() {
    for (int i = 0; i <= 100; i++) {
        Xseq[i] = Yseq[i] = '-';
    }
}

int main() {
    int t;
    ifstream ifile;
    ifile.open("input.txt");  // 파일 열기
    if(ifile.is_open()) {
        ifile >> t; // testcase 개수
        for (int i = 0; i < t; i++) {
            init_seq();
            ifile >> m;
            for (int j = 1; j <= m; j++) {
                ifile >> Xseq[j];
            }
            ifile >> n;
            for (int j = 1; j <= n; j++) {
                ifile >> Yseq[j];
            }
            opt();
            align(m, n);
            int bigger = (m > n) ? m : n;
            for (int i = 1; i <= 2; i++) {
                for (int j = 1; j <= bigger; j++) {
                    cout << align_ans[i][j];
                }
                cout << '\n';
            }
            for (int i = 0; i <= m; i++) {
                for (int j = 0; j <= n; j++) {
                    cout << O[i][j] << ' ';
                }
                cout << '\n';
            }
        }
    }
    ifile.close(); // 파일 닫기
    return 0;
}

