// Problem: D. Prefixes and Suffixes
// Link: https://codeforces.com/problemset/problem/432/D
// Author: Mai Thanh Hiep
// Complexity: O(S), where S is the length of string

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> computeKMPTable(string &pattern) {
    int n = pattern.size();
    vector<int> lps(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && pattern[i] != pattern[j]) j = lps[j - 1];
        if (pattern[i] == pattern[j]) lps[i] = ++j;
    }
    return lps;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    string str;
    cin >> str;

    int n = str.size();
    vector<int> lps = computeKMPTable(str);

    vector<int> dp(n + 1); // dp[i] is the number of occurrences of prefix length `i`
    for (int i = 0; i <= n; i++)
        dp[i] = 1;

    for (int i = n; i >= 1; i--)
        dp[lps[i - 1]] += dp[i];

    vector<pair<int, int>> ans;
    int l = n;
    while (l > 0) {
        ans.emplace_back(l, dp[l]);
        l = lps[l-1];
    }

    cout << ans.size() << endl;
    for (int i = (int)ans.size() - 1; i >= 0; --i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}