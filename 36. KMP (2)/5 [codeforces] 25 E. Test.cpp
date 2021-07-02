// Problem: 25 E. Test
// Link: https://codeforces.com/problemset/problem/25/E
// Author: Mai Thanh Hiep
// Complexity: O(6 *N) ~ O(N), where where N <= 10^5 is length of each string.

#include <iostream>
#include <vector>
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

string combine(string& str1, string& str2) { // O(N)
    if (search(str1, str2)) return str1;
    if (search(str2, str1)) return str2;
    int m = str1.size(), n = str2.size();
    string concat = str2 + "#" + str1; // Example: str1 = "abc", str2 = "bcd" -> concat = "bcd#abc" -> overlapLen=2
    vector<int> lps = computeKMP(concat);
    int overlapLen = lps[concat.size() - 1];
    return str1 + str2.substr(overlapLen, n - overlapLen);
}

int merge(string& str1, string& str2, string& str3) { // O(N)
    string res = combine(str1, str2);
    return combine(res, str3).size();
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string strs[3];
    for (int i = 0; i < 3; ++i) cin >> strs[i];
    int ans = strs[0].size() + strs[1].size() + strs[2].size();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i != j && j != k && i != k) { // there are total 6 combination (3 ways choose first pos, 2 ways choose second pos, 1 way choose last pos)
                    ans = min(ans, merge(strs[i], strs[j], strs[k]));
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}