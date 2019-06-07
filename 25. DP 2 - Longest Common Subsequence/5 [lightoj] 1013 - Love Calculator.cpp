// Problem: 1013 - Love Calculator
// Link: http://lightoj.com/volume_showproblem.php?problem=1013
// Author: Mai Thanh Hiep
// Complexity: T * O(|str1| * |str2|); T <= 125, |str1|, |str2| <= 30

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

#define MAX 30 // The names will contain no more than 30 capital letters.
int dp[MAX + 1][MAX + 1];
ll num[MAX + 1][MAX + 1];

// O(N1 * N2)
int longestCommonSubsequence(string& arr1, int n1, string& arr2, int n2) {
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
                num[i][j] = 1;
            } else if (arr1[i - 1] == arr2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                num[i][j] = num[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                num[i][j] = 0;
                if (dp[i - 1][j] >= dp[i][j - 1])
                    num[i][j] += num[i - 1][j];
                if (dp[i][j - 1] >= dp[i - 1][j])
                    num[i][j] += num[i][j - 1];
            }
        }
    }
    return dp[n1][n2];
}

int main() {
    int t;
    cin >> t;

    string str1, str2;
    for (int tc = 1; tc <= t; tc++) {
        cin >> str1 >> str2;
        int len1 = str1.size();
        int len2 = str2.size();
        int lcs = longestCommonSubsequence(str1, len1, str2, len2); // O(|str1| * |str2|); |str1|, |str2| <= 30 -> This is complexity of this solution

        cout << "Case " << tc << ": ";
        cout << (len1 + len2 - lcs) << " " << num[len1][len2] << endl;
    }

    return 0;
}