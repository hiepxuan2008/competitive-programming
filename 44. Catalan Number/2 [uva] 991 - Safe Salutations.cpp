// Problem: 991 - Safe Salutations
// Link: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=932
// Author: Mai Thanh Hiep
// Complexity: O(T * 11), where T is number of testcases

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll C[11];
    C[0] = C[1] = 1LL;
    for (int i = 1; i < 10; ++i)
        C[i + 1] = (4 * i + 2) * C[i] / (i + 2);

    int n;
    while (cin >> n) {
        cout << C[n] << '\n';
    }

    return 0;
}