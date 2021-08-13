// Problem: NUMOFPAL - Number of Palindromes
// Link: https://www.spoj.com/problems/NUMOFPAL/
// Author: Mai Thanh Hiep
// Complexity: O(N), where N <= 1000 is the length of string.

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

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    string t(2 * n + 1, '#');
    for (int i = 0; i < n; ++i)
        t[2 * i + 1] = s[i];

    vector<int> p = manacher(t);
    int ans = 0;
    for (int i = 1; i < p.size() - 1; ++i) {
        if (p[i] > 0) {
//            string pal = s.substr((i - p[i])/2, p[i]);
//            cout << pal << '\n';
            ans += (p[i]+1)/2;
        }
    }
    cout << ans << '\n';

    return 0;
}