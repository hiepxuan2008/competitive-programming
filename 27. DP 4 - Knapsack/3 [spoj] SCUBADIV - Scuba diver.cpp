// Problem: SCUBADIV - Scuba diver
// Link: https://vn.spoj.com/problems/SCUBADIV/
// Author: Mai Thanh Hiep
// Complexity: TC * O(N * T * A), N <= 1000, T <= 21, A <= 79

#include <iostream>
#include <algorithm>
#include <limits.h>
#include <vector>
using namespace std;
#define INF 800 * 1000 + 1

// O(N * T * A)
int solve01Knapsack(const vector<int>& tArr, const vector<int>& aArr, const vector<int>& wArr, int n, int t, int a) {
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(t + 1, vector<int>(a + 1)));
	int itemIndex;
	int weight;
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= t; j++) {
			for (int k = 0; k <= a; k++) {
				if (i == 0) { // no item
					if (j == 0 && k == 0) {
						dp[i][j][k] = 0;
					}
					else {
						dp[i][j][k] = INF; // can't feed i, j
					}
				}
				else {
					itemIndex = i - 1;

					// if we don't take item itemIndex
					dp[i][j][k] = dp[i - 1][j][k]; 

					// if we take item itemIndex
					weight = dp[i - 1][max(j - tArr[itemIndex], 0)][max(0, k - aArr[itemIndex])];
					if (weight != INF) {
						dp[i][j][k] = min(dp[i][j][k], weight + wArr[itemIndex]);
					}
				}
			}
		}
	}

	return dp[n][t][a];
}

int main() {
	int T;
	cin >> T;

	int t, a, n;
	while (T--) {
		cin >> t >> a;
		cin >> n;

		vector<int> tArr(n), aArr(n), wArr(n);
		for (int i = 0; i < n; i++) {
			cin >> tArr[i] >> aArr[i] >> wArr[i];
		}

		cout << solve01Knapsack(tArr, aArr, wArr, n, t, a) << endl;
	}

	return 0;
}