// Problem: 10312 - Expression Bracketing
// Link: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1253
// Author: Mai Thanh Hiep
// Complexity: O(T * 30), where T is number of testcases
/**
 * Number of full binary tree of N leaves is a Catalan of (N-1)th
 * Total tree of N leaves (where non-leaf nodes have at least 2 children) is a Super Catalan of N
 * Result = SC[N] - C[N-1]
 */ 

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

    ll C[27], SC[27];
    C[0] = C[1] = 1LL;
    for (int i = 1; i < 26; ++i)
        C[i + 1] = (4 * i + 2) * C[i] / (i + 2);

    SC[1] = SC[2] = 1LL;
    for (int i = 3; i <= 26; ++i)
        SC[i] = ((6 * i - 9) * SC[i - 1] - (i - 3) * SC[i - 2]) / i;

    int n;
    while (cin >> n) {
        cout << SC[n] - C[n - 1] << '\n';
    }

    return 0;
}