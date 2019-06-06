// Problem: 231 - Testing the CATCHER
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=167
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2)

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 100000
int arr[MAX];
int dp[MAX];

// O(N^2)
int longestNotIncreasingSubsequence(int n) {
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] <= arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++)
        result = max(result, dp[i]);
    return result;
}

int main() {
    int n = 0, x;
    int tc = 0;
    while (cin >> x) {
        if (x == -1)
            break;

        n = 0;
        arr[n++] = x;
        while (cin >> x) {
            if (x == -1)
                break;
            arr[n++] = x;
        }

        tc++;
        if (tc > 1)
            cout << endl;

        cout << "Test #" << tc << ":" << endl;
        cout << "  maximum possible interceptions: " << longestNotIncreasingSubsequence(n) << endl;
    }

    return 0;
}