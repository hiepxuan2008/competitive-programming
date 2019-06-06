// Problem: BYTESM2 - Philosophers Stone
// Link: https://www.spoj.com/problems/BYTESM2/
// Author: Mai Thanh Hiep
// Complixity:
//			Time: T * O(H * W); H, W <= MAX = 100
//			Space: O(MAX), MAX = 100

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 100

int main() {
    int t, h, w;
    cin >> t;

    long long dp[2][MAX];
    int arr[2][MAX];

    while (t--) {
        cin >> h >> w;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> arr[i % 2][j];
            }

            for (int j = 0; j < w; j++) {
                if (i == 0) { // base dp
                    dp[0][j] = arr[0][j];
                } else { // dp[i][j] = max(dp[i-1][j], dp[i-1][j-1], dp[i-1][j+1]) + arr[i][j]
                    dp[i % 2][j] = dp[(i - 1) % 2][j];
                    if (j + 1 < w)
                        dp[i % 2][j] = max(dp[i % 2][j], dp[(i - 1) % 2][j + 1]);
                    if (j - 1 >= 0)
                        dp[i % 2][j] = max(dp[i % 2][j], dp[(i - 1) % 2][j - 1]);
                    dp[i % 2][j] += arr[i % 2][j];
                }
            }
        }

        long long ans = 0;
        for (int j = 0; j < w; j++)
            ans = max(dp[(h - 1) % 2][j], ans);
        cout << ans << endl;
    }

    return 0;
}