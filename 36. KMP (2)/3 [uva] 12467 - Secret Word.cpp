// Problem: 12467 - Secret Word
// Link: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3911
// Author: Mai Thanh Hiep
// Complexity: O(T * N * logN), where T <= 150 is number of testcases, where N <= 10^6 is length of each string.

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

bool search(string& T, string& P) {
    vector<int> lps = computeKMP(P);
    int n = T.size(), j = 0, m = P.size();
    for (int i = 0; i < n; ++i) {
        while (j > 0 && T[i] != P[j]) j = lps[j-1];
        if (T[i] == P[j]) ++j;
        if (j == m) return true;
    }
    return false;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        int left = 0, right = n - 1;
        string ans = "";
        while (left <= right) { // O(N * logN)
            int mid = (left + right) >> 1;
            string pattern = s.substr(0, mid + 1);
            reverse(pattern.begin(), pattern.end());
            if (search(s, pattern)) { // O(N)
                ans = pattern;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}