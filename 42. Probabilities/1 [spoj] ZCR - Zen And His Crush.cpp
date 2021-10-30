// Problem: ZCR - Zen And His Crush
// Link: https://www.spoj.com/problems/ZCR/
// Author: Mai Thanh Hiep
// Complexity: O(T * N * K), where T <= 100 is number of testcases, N <= 1000 is number coins, K <= N is number of expected heads.
/**
 * Idea:
 *  dp[i][j] is the probability, throw i coins and have j heads
 *  Base case: dp[i][0] = 1
 *  Transition state: dp[i][j] = dp[i-1][j] * (1-p[i]) + dp[i-1][j-1] * p[i]
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1005;
double p[MAXN];
double dp[MAXN][MAXN];

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n, k;
    cin >> t;

    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
        }
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = 1;
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i-1][j] * (1-p[i]) + dp[i-1][j-1] * p[i];
            }
        }
        cout << dp[n][k] << '\n';
    }

    return 0;
}