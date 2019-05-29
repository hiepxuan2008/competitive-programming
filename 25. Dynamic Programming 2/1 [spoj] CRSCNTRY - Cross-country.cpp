// Problem: CRSCNTRY - Cross-country
// Link: https://vn.spoj.com/problems/CRSCNTRY/
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2); T <= 10, N <= 2000

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAXN 2000

int input(int* arr) {
	int x;
	int n = 0;
	while (cin >> x) {
		if (x == 0)
			break;
		arr[n++] = x;
	}
	return n;
}

int dp[MAXN + 1][MAXN + 1];
// O(N1 * N2)
int longestCommonSubsequence(int* arr1, int n1, int* arr2, int n2) {
	for (int i = 0; i <= n1; i++) {
		for (int j = 0; j <= n2; j++) {
			if (i == 0 || j == 0)
				dp[i][j] = 0;
			else if (arr1[i - 1] == arr2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[n1][n2];
}

int main() {
	int t;
	cin >> t;
	int arr1[MAXN];
	int n1, n2;
	int arr2[MAXN];
	int ans;

	while (t--) {
		n1 = input(arr1);
		ans = 0;
		while (true) {
			n2 = input(arr2);
			if (n2 == 0)
				break;

			ans = max(ans, longestCommonSubsequence(arr1, n1, arr2, n2));
		}
		cout << ans << endl;
	}

	return 0;
}