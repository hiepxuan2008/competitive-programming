// Problem: 10534 - Wavio Sequence
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1475
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2), T < 75, N <= 10000
// Status: Time Limit Exceeded!

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 10001
int arr[MAX];
int dpIncreasing[MAX];
int dpDescreasing[MAX];

// O(N^2)
int longestWavioSubsequence(int n) {
	for (int i = 0; i < n; i++) {
		dpIncreasing[i] = 1;
		dpDescreasing[i] = 1;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[i] > arr[j] && dpIncreasing[i] < dpIncreasing[j] + 1) {
				dpIncreasing[i] = dpIncreasing[j] + 1;
			}
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j > i; j--) {
			if (arr[i] > arr[j] && dpDescreasing[i] < dpDescreasing[j] + 1) {
				dpDescreasing[i] = dpDescreasing[j] + 1;
			}
		}
	}

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