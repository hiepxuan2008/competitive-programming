// Problem: LCS - Longest Common Substring
// Link: https://www.spoj.com/problems/LCS/
// Author: Mai Thanh Hiep
// Complexity: O(M * N), where M <= 250000 is the length of str1, N <= 250000 is the length of str2 (Time Limit Exceed)

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int solve(const string& str1, const string& str2) {
    int m = str1.size(), n = str2.size();
    vector<int> dp(n+1), dpPrev(n+1);
    int ans = 0;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (str1[i-1] == str2[j-1]) {
                dp[j] = dpPrev[j-1] + 1;
            } else {
                dp[j] = 0;
            }
            ans = max(ans, dp[j]);
        }
        dp.swap(dpPrev);
    }
    return ans;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    cin >> str1 >> str2;

    cout << solve(str1, str2) << '\n';

    return 0;
}