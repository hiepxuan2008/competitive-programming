// Problem: 990 - Diving for Gold
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=931
// Author: Mai Thanh Hiep
// Complexity: TEST_CASE * O(N * T), T <= 1000, N <= 30

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

void getPickedItems(const vector<vector<int>>& dp, const vector<int>& weights, int n, int w, vector<int>& pickedItems) {
	int itemIndex;
	for (int i = n; i > 0; i--) {
		if (dp[i][w] != dp[i - 1][w]) {
			itemIndex = i - 1;
			pickedItems.push_back(itemIndex);
			w -= weights[itemIndex];
		}
	}
}

// O(N * W)
int solve01Knapsack(const vector<int> weights, const vector<int> profits, int n, int w, vector<int>& pickedItems) {
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

	getPickedItems(dp, weights, n, w, pickedItems);

	return dp[n][w];
}

int main() {
	int t, w, n;
	int TEST_CASE = 0;
	while (cin >> t >> w >> n) {
		TEST_CASE++;
		if (TEST_CASE > 1)
			cout << endl;

		vector<int> depths(n), quantities(n), costs(n);

		for (int i = 0; i < n; i++) {
			cin >> depths[i] >> quantities[i];
			costs[i] = 3 * depths[i] * w; // time cost for taken treasure i_th
		}

		vector<int> recoverItems;
		cout << solve01Knapsack(costs, quantities, n, t, recoverItems) << endl; // O(N * T), T <= 1000, N <= 30 -> This is complexity of this solution

		int itemSize = recoverItems.size();
		int itemIndex;
		cout << itemSize << endl;
		for (int i = itemSize - 1; i >= 0; i--) {
			itemIndex = recoverItems[i];
			cout << depths[itemIndex] << " " << quantities[itemIndex] << endl;
		}
	}

	return 0;
}