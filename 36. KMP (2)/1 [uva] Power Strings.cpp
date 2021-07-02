// Problem: Power Strings
// Link: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1239
// Author: Mai Thanh Hiep
// Complexity: O(T * N), where T is number of testcases, N <= 10^6 is length of string s.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

vector<int> computeKMP(string& P) {
    int m = P.size();
    vector<int> lps(m);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && P[i] != P[j]) j = lps[j-1];
        if (P[i] == P[j]) lps[i] = ++j;
    }
    return lps;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (cin >> s && s != ".") {
        int n = s.size();
        vector<int> lps = computeKMP(s); // O(N)
        int size = n - lps[n-1];
        if (n % size == 0) {
            cout << (n / size) << '\n';
        } else {
            cout << 1 << '\n';
        }
    }
    return 0;
}