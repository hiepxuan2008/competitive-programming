// Problem: PPTEST - Polo the Penguin and the Test
// Link: https://www.codechef.com/problems/PPTEST
// Author: Mai Thanh Hiep
// Complexity: T * O(N * W), T, N, W <= 100

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 101
#define MAXW 101
int weights[MAXN];
int profits[MAXN];

// O(N * W)
int solve01Knapsack(int n, int w) {
	vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
	int itemIndex;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= w; j++) {
			itemIndex = i - 1;
			dp[i][j] = dp[i - 1][j];
			if (j >= weights[itemIndex]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - weights[itemIndex]] + profits[itemIndex]);
			}
		}
	}
	return dp[n][w];
}

int main() {
	int T;
	cin >> T;

	int N, W;
	int c, p, t;
	while (T--) {
		cin >> N >> W;
		for (int i = 0; i < N; i++) {
			cin >> c >> p >> t;
			profits[i] = c * p;
			weights[i] = t;
		}

		cout << solve01Knapsack(N, W) << endl;
	}

	return 0;
}