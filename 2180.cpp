#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int MAX = 40001;
ll n, sum=0;
vector<tuple<double, int, int>> v;

void print() {
    for (int i = 0; i < n; i++) {
        cout << get<0>(v[i]) << " " << get<1>(v[i]) << " " << get<2>(v[i]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        if (a == 0) v.push_back(make_tuple(MAX, a, b));
        // 튜플에 MAX를 넣어 정렬 시 맨 뒤
        else v.push_back(make_tuple(b/a, a, b));
    }
    sort(v.begin(), v.end());
   // print();
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        sum += get<1>(v[i]) * t + get<2>(v[i]);
        sum %= 40000;
        t = sum;
    }
    cout << sum;
    return 0;
}
