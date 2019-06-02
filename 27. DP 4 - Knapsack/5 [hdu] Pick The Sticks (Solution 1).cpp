// Problem: Pick The Sticks
// Link: http://acm.hdu.edu.cn/showproblem.php?pid=5543
// Author: Mai Thanh Hiep
// Complexity: 
//          Time: T * O(N * L), N <= 500, L <= 1000, T <= 100
//          Space: O(N * L)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

// O(N * W)
ll solve01Knapsack(const vector<int> weights, const vector<int> profits, int n, int w) {
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(w + 1, vector<ll>(3, 0)));

    int itemIndex;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            for (int k = 0; k <= 2; k++) { // k = 0: can't put the gold stick outside the container, k = 1: can put outside 1 side of the container, k = 2: can put outside 2 sides of the container
                if (i == 0) {
                    dp[i][j][k] = 0;
                } else {
                    itemIndex = i - 1;

                    // don't take item i_th
                    dp[i][j][k] = dp[i - 1][j][k];

                    // try to put the whole item i_th to the container
                    if (j >= 2 * weights[itemIndex]) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 2 * weights[itemIndex]][k] + profits[itemIndex]);
                    }

                    // try to put a half of item i_th to the container
                    if (j >= weights[itemIndex] && k > 0) { // k > 0 means can put the gold stick outside the container 
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - weights[itemIndex]][k - 1] + profits[itemIndex]);
                    }
                }
            }
        }
    }

    return dp[n][w][2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    int N, L;
    for (int tc = 1; tc <= t; tc++) {
        cin >> N >> L;
        vector<int> lengths(N), values(N);

        ll ans = 0;
        for (int i = 0; i < N; i++) {
            cin >> lengths[i] >> values[i];
            ans = max(ans, (ll)values[i]); // put only this item to center of this item to the container
        }

        ans = max(ans, solve01Knapsack(lengths, values, N, 2 * L)); // O(N * 2L), N <= 500, L <= 1000 -> This is complexity of this solution

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}