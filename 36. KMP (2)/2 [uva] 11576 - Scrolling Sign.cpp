// Problem: 11576 - Scrolling Sign
// Link: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2623
// Author: Mai Thanh Hiep
// Complexity: O(T * N * M * M), where T is number of testcases, N, M <= 100 is number of words and length of each word corresponding.

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

string mergeOverlap(string& str1, string& str2) {
    int m = str1.size(), n = str2.size();
    string concat = str2 + "#" + str1; // Example: str1 = "abc", str2 = "bcd" -> concat = "bcd#abc" -> overlapLen=2
    vector<int> lps = computeKMP(concat);
    int overlapLen = lps[concat.size() - 1];
    return str1 + str2.substr(overlapLen, n - overlapLen);
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, m, n;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        string ans;
        cin >> ans;
        for (int i = 1; i < n; ++i) { // O(N * M * M)
            string str;
            cin >> str;
            ans = mergeOverlap(ans, str);
        }
        cout << ans.size() << '\n';
    }
    return 0;
}