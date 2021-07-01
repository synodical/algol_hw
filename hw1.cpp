#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int tree[1001][2] = {-1, };
int ans = 0;
int l = 0; int r = 0;

int height(int root) {
    if(root == -1) return 0;
    int hLeft = height(tree[root][0]);
    int hRight = height(tree[root][1]);
    return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}

void preorder(int root) { // VLR, 이걸 좀 수정해서 답 내는 함수로...
    if(root == -1) return;
    int lH;
    int rH;
    lH = height(tree[root][0]);
    rH = height(tree[root][1]);
    if(lH < rH) ans++; // 오른쪽 subtree node 개수가 더 많을 때
    
    preorder(tree[root][0]); // lc
    preorder(tree[root][1]); // rc
}

int main() {
    ifstream ifile;
      
    ifile.open("input.txt");  // 파일 열기

    if(ifile.is_open()) {
//       while(!ifile.eof()) {
            int t;
            ifile >> t; // testcase 개수
            for (int i = 0; i < t; i++) {
                int N; // 1 <= N <= 1000
                ifile >> N;
                for (int j = 0; j < N; j++) {
                    int root, lc, rc;
                    ifile >> root >> lc >> rc;
                    tree[root][0] = lc;
                    tree[root][1] = rc;
                }
                preorder(1);
                cout << ans;
                cout << '\n';
                ans = 0;
                /*트리 초기화... fill 기억 안나서 걍 for문으로*/
                for (int i = 0; i < 1001; i++) {
                    for (int j = 0; j < 2; j++) {
                        tree[i][j] = -1;
                    }
                }
            }
  //      }
    }
    ifile.close(); // 파일 닫기

    return 0;
}

