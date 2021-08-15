#include <iostream>
#include <vector>
using namespace std;
const int MAX = 13;
const int edge = 12;
int adj[MAX][MAX];
int degree[MAX];

void spica() {
    for (int i = 1; i <= edge; i++) {
        bool first = false;
        bool second = false;
        bool third = false;
        
        if (degree[i] == 3) {
            for (int j = 1; j <= edge; j++) {
                if (adj[i][j] && degree[j] == 1) first = true;
                if (adj[i][j] && degree[j] == 2) second = true;
                if (adj[i][j] && degree[j] == 3) third = true;
            }
        }
        if (first && second && third) cout << i;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    for (int i = 0; i < edge; i++) {
        int x, y; // 1 <= x,y <= 12
        cin >> x >> y;
        adj[x][y] = 1;
        adj[y][x] = 1;
        degree[x]++;
        degree[y]++;
    }
    // print degree of each nodes
    // for (int i = 1; i <= edge; i++) cout << degree[i] << '\n';
    spica();
    
    return 0;
}
