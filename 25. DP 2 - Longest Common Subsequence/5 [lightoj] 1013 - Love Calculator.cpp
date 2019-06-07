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
int findShortestStringContainOriginalStringsAsSubsequence(string& arr1, int n1, string& arr2, int n2) {
    for (int i = 0; i <= n1; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n2; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (arr1[i - 1] == arr2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
        }
    }
    return dp[n1][n2];
}

// O(N1 * N2)
ll computeWays(string& arr1, int n1, string& arr2, int n2) {
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0)
                num[i][j] = 1;
            else if (arr1[i - 1] == arr2[j - 1]) {
                num[i][j] = num[i - 1][j - 1];
            } else {
                if (dp[i - 1][j] < dp[i][j - 1])
                    num[i][j] = num[i - 1][j]; // pick num ways of shortest string
                else if (dp[i - 1][j] > dp[i][j - 1])
                    num[i][j] = num[i][j - 1]; // pick num ways of shortest string
                else
                    num[i][j] = num[i - 1][j] + num[i][j - 1];
            }
        }
    }
    return num[n1][n2];
}

int main() {
    int t;
    cin >> t;

    string str1, str2;
    for (int tc = 1; tc <= t; tc++) {
        cin >> str1 >> str2;
        int len1 = str1.size();
        int len2 = str2.size();
        int shortestLength = findShortestStringContainOriginalStringsAsSubsequence(str1, len1, str2, len2); // O(|str1| * |str2|); |str1|, |str2| <= 30 -> This is complexity of this solution
        ll ways = computeWays(str1, len1, str2, len2); // O(|str1| * |str2|); |str1|, |str2|

        cout << "Case " << tc << ": ";
        cout << shortestLength << " " << ways << endl;
    }

    return 0;
}