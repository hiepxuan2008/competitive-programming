// Problem: MSUBSTR - Mirror Strings !!!
// Link: https://www.spoj.com/problems/MSUBSTR/en/
// Author: Mai Thanh Hiep
// Complexity: O(T * N), where N <= 10^5 is the length of string, T <= 200 is number of testcases.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

// Time complexity: O(|S|)
vector<int> manacher(const string &s) {
    int n = s.length();
    vector<int> p(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 0 : min(p[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
            ++k;
        p[i] = --k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return p;
}

void solve(const string& s) {
    int n = s.size();
    string t(2 * n + 1, '#');
    for (int i = 0; i < n; ++i)
        t[2 * i + 1] = s[i];
    vector<int> p = manacher(t);
    int ansLen = 0;
    int ansTimes = 0;
    for (int i = 1; i < p.size() - 1; ++i) {
        if (ansLen < p[i]) {
            ansLen = p[i];
            ansTimes = 1;
        } else if (ansLen == p[i]) {
            ++ansTimes;
        }
    }
    cout << ansLen << " " << ansTimes << '\n';
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nTestcase;
    cin >> nTestcase;
    string s;
    while (nTestcase--) {
        cin >> s;
        solve(s);
    }

    return 0;
}