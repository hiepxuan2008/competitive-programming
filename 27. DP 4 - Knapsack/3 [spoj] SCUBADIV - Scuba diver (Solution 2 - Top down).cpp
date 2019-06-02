// Problem: SCUBADIV - Scuba diver
// Link: https://www.spoj.com/problems/SCUBADIV/
// Author: Mai Thanh Hiep
// Complexity: TC * O(N * T * A), N <= 1000, T <= 21, A <= 79

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 800 * 1000 + 1
#define MAX_OXYGEN 21
#define MAX_INTROGEN 79
#define MAX_N 1000

int dp[MAX_N + 1][MAX_OXYGEN + 1][MAX_INTROGEN + 1];
int oxygens[MAX_N], nitrogens[MAX_N], weights[MAX_N];

// O(N * T * A)
int solve01Knapsack(int n, int oxygenNeed, int nitrogenNeed) {
    if (oxygenNeed == 0 && nitrogenNeed == 0)
        return 0; // no weight need

    if (n == 0)
        return INF; // no item -> can't feed oxygenNeed or nitrogenNeed

    if (dp[n][oxygenNeed][nitrogenNeed] == -1) {
        int itemIndex = n - 1;

        // if we don't take item itemIndex
        dp[n][oxygenNeed][nitrogenNeed] = solve01Knapsack(n - 1, oxygenNeed, nitrogenNeed);

        // if we take item itemIndex
        int _oxyNeed = max(oxygenNeed - oxygens[itemIndex], 0);
        int _nitroNeed = max(nitrogenNeed - nitrogens[itemIndex], 0);
        int weight = solve01Knapsack(n - 1, _oxyNeed, _nitroNeed);
        if (weight != INF) {
            dp[n][oxygenNeed][nitrogenNeed] = min(dp[n][oxygenNeed][nitrogenNeed], weight + weights[itemIndex]);
        }
    }

    return dp[n][oxygenNeed][nitrogenNeed];
}

int main() {
    int T;
    cin >> T;

    int oxygenNeed, nitrogenNeed, n;
    while (T--) {
        cin >> oxygenNeed >> nitrogenNeed;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cin >> oxygens[i] >> nitrogens[i] >> weights[i];
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= oxygenNeed; j++) {
                for (int k = 0; k <= nitrogenNeed; k++)
                    dp[i][j][k] = -1;
            }
        }

        cout << solve01Knapsack(n, oxygenNeed, nitrogenNeed) << endl;
    }

    return 0;
}