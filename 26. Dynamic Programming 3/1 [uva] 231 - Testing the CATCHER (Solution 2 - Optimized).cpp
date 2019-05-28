// Problem: 231 - Testing the CATCHER
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=167
// Author: Mai Thanh Hiep
// Complexity: T * O(NLogN)

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 100000
int arr[MAX];
int dp[MAX];

int firstElementLessThanXInDecreasingArr(const vector<int>& indices, int left, int right, int x) {
	int pos = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[indices[mid]] < x) {
			pos = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return pos;
}

// O(NlogN)
int longestIncreasingSubsequenceBinarySearch(int n) {
	int length = 1;
	vector<int> result;
	result.push_back(0);

	for (int i = 0; i < n; i++)
		dp[i] = 1;

	for (int i = 1; i < n; i++) {
		if (arr[i] <= arr[result[length - 1]]) { // insert to result
			//path[i] = result[length - 1];
			dp[i] = dp[result[length - 1]] + 1;
			result.push_back(i);
			length++;
		}
		else { // arr[result[pos]] as max as possible
			int pos = firstElementLessThanXInDecreasingArr(result, 0, length - 1, arr[i]);
			if (pos > 0) {
				dp[i] = dp[result[pos - 1]] + 1;
				//path[i] = result[pos - 1];
			}
			result[pos] = i;
		}
	}

	return dp[result[length - 1]];
}

int main() {
	int n = 0, x;
	int tc = 0;
	while (cin >> x) {
		if (x == -1)
			break;

		n = 0;
		arr[n++] = x;
		while (cin >> x) {
			if (x == -1)
				break;
			arr[n++] = x;
		}

		tc++;
		if (tc > 1)
			cout << endl;

		cout << "Test #" << tc << ":" << endl;
		cout << "  maximum possible interceptions: " << longestIncreasingSubsequenceBinarySearch(n) << endl;
	}

	return 0;
}