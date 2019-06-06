// Problem: AIBOHP - Aibohphobia
// Link: https://www.spoj.com/problems/AIBOHP/
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2), N <= 6100

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAXN 6100

int dp[MAXN + 1][MAXN + 1];
// O(N1 * N2)
int longestCommonSubsequence(string& arr1, int n1, string& arr2, int n2) {
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (arr1[i - 1] == arr2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n1][n2];
}

string reverse(const string& s) {
    string result = s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        result[i] = s[n - i - 1];
    }
    return result;
}

int main() {
    int t;
    cin >> t;

    string s, sReverse;
    int len;
    while (t--) {
        cin >> s;
        sReverse = reverse(s);
        len = s.size();
        cout << (len - longestCommonSubsequence(s, len, sReverse, len)) << endl;
    }

    return 0;
}