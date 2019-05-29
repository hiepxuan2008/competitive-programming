// Problem: 562 - Dividing coins
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=503
// Author: Mai Thanh Hiep
// Complexity: T * O(M^2), M <= 100

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100
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

	int m;
	while (T--) {
		cin >> m;

		int sum = 0;
		for (int i = 0; i < m; i++) {
			cin >> profits[i];
			sum += profits[i];
			weights[i] = profits[i];
		}

		int minHalf = solve01Knapsack(m, sum / 2); // O(M^2), M <= 100 -> This is complexity of this solution
		cout << (sum - minHalf - minHalf) << endl;
	}

	return 0;
}