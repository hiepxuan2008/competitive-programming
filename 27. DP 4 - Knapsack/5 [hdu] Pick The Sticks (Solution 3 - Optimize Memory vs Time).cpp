// Problem: Pick The Sticks
// Link: http://acm.hdu.edu.cn/showproblem.php?pid=5543
// Author: Mai Thanh Hiep
// Complexity: T * O(N * L), N <= 500, L <= 1000, T <= 100

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

// O(N * W)
ll solve01Knapsack(const vector<int> weights, const vector<int> profits, int n, int w) {
    vector<vector<ll>> dp(w + 1, vector<ll>(3, 0));

    ll maxProfit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = w; j >= weights[i]; j--) { // reverse to reuse previous data in row (i-1)th
            for (int k = 0; k <= 2; k++) { // k = 0: can't put the gold stick outside the container, k = 1: can put outside 1 side of the container, k = 2: can put outside 2 sides of the container

                // try to put the whole item i_th to the container
                if (j >= 2 * weights[i]) {
                    dp[j][k] = max(dp[j][k], dp[j - 2 * weights[i]][k] + profits[i]);
                }

                // try to put a half of item i_th to the container
                if (j >= weights[i] && k > 0) { // k > 0 means can put the gold stick outside the container 
                    dp[j][k] = max(dp[j][k], dp[j - weights[i]][k - 1] + profits[i]);
                }

                maxProfit = max(maxProfit, dp[j][k]);
            }
        }
    }

    return dp[w][2];
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