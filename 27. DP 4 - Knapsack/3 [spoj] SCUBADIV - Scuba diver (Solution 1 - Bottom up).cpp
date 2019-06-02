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
    int itemIndex;
    int weight;
    int _oxyNeed;
    int _nitroNeed;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= oxygenNeed; j++) {
            for (int k = 0; k <= nitrogenNeed; k++) {
                if (i == 0) { // no item
                    if (j == 0 && k == 0) {
                        dp[i][j][k] = 0;
                    } else {
                        dp[i][j][k] = INF; // can't feed i, j
                    }
                } else {
                    itemIndex = i - 1;

                    // if we don't take item itemIndex
                    dp[i][j][k] = dp[i - 1][j][k];

                    // if we take item itemIndex
                    _oxyNeed = max(j - oxygens[itemIndex], 0);
                    _nitroNeed = max(0, k - nitrogens[itemIndex]);
                    weight = dp[i - 1][_oxyNeed][_nitroNeed];
                    if (weight != INF) {
                        dp[i][j][k] = min(dp[i][j][k], weight + weights[itemIndex]);
                    }
                }
            }
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

        cout << solve01Knapsack(n, oxygenNeed, nitrogenNeed) << endl;
    }

    return 0;
}