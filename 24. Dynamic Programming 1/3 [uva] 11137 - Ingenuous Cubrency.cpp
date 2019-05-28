// Problem: 11137 - Ingenuous Cubrency
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2078
// Author: Mai Thanh Hiep
// Complexity: O(COIN_SIZE * MAXN); COIN_SIZE = 21, MAXN = 10^4

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define COIN_SIZE 21
#define MAXN 10000

int main() {
	vector<int> coins(COIN_SIZE + 1);
	for (int i = 1; i <= COIN_SIZE; i++)
		coins[i] = i * i * i;

	vector<ll> dp(MAXN, 0);
	dp[0] = 1;
	for (int i = 1; i <= COIN_SIZE; i++) {
		for (int j = coins[i]; j < MAXN; j++) {
			dp[j] += dp[j - coins[i]];
		}
	}

	int n;
	while (cin >> n) {
		cout << dp[n] << endl;
	}

	return 0;
}