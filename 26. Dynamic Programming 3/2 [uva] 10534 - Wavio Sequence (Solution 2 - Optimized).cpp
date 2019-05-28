// Problem: 10534 - Wavio Sequence
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1475
// Author: Mai Thanh Hiep
// Complexity: T * O(NlogN), T < 75, N <= 10000
// Status: Accepted!

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 10001
int arr[MAX];
int dpIncreasing[MAX];
int dpDescreasing[MAX];

// also we call it upper_bound
int findFirstElementGreaterThanOrEqualXInIncreasingArray(const vector<int>& indices, int left, int right, int x) {
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[indices[mid]] >= x && (mid == left || arr[indices[mid - 1]] < x))
			return mid;
		else if (arr[indices[mid]] < x) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}

// O(NlogN)
int longestIncreasingSubsequenceBinarySearch(int n, int* dp) {
	int length = 1;
	vector<int> result;
	result.push_back(0);

	for (int i = 0; i < n; i++)
		dp[i] = 1;

	for (int i = 1; i < n; i++) {
		if (arr[i] > arr[result[length - 1]]) { // insert to result
			//path[i] = result[length - 1];
			dp[i] = dp[result[length - 1]] + 1;
			result.push_back(i);
			length++;
		}
		else { // make arr[result[pos]] as min as possible
			int pos = findFirstElementGreaterThanOrEqualXInIncreasingArray(result, 0, length - 1, arr[i]);
			if (pos > 0) {
				dp[i] = dp[result[pos - 1]] + 1;
				//path[i] = result[pos - 1];
			}
			result[pos] = i;
		}
	}

	return dp[result[length - 1]];
}

void reverse(int* arr, int n) {
	for (int i = 0; i < n / 2; i++)
		swap(arr[i], arr[n - 1 - i]);
}

// O(NlogN)
int longestWavioSubsequence(int n) {
	// calculate dpIncreasing
	longestIncreasingSubsequenceBinarySearch(n, dpIncreasing);

	// calculate dpDescreasing
	reverse(arr, n);
	longestIncreasingSubsequenceBinarySearch(n, dpDescreasing);
	reverse(dpDescreasing, n);

	int result = 0;
	for (int i = 0; i < n; i++) {
		result = max(result, min(dpIncreasing[i], dpDescreasing[i]) * 2);
	}
	return result - 1;
}

int main() {
	int n = 0;
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		cout << longestWavioSubsequence(n) << endl;
	}

	return 0;
}