// Problem: 441 - Lotto
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=382
// Author: Mai Thanh Hiep
// Complexity: C(k, 6) = k! / (6! * (k-6)! = (k-5)*(k-4)*(k-3)*(k-2)*(k-1)*k/6!) ~ k^6
//			=> O(k^6)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define NUM_LETTERS 6

void printVector(const vector<int>& result) {
	int n = result.size();
	for (int i = 0; i < n - 1; i++)
		cout << result[i] << " ";

	cout << result[n-1] << endl;
}

void backtracking(const vector<int>& S, vector<int>& result, int s, int i) {
	if (i == NUM_LETTERS) {
		printVector(result);
	} else {
		// Since S are already sorted in ascending order, S[s] > S[i], 0 <= i < s
		for (int j = s; j < S.size(); j++) {
			result[i] = S[j];
			backtracking(S, result, j + 1, i + 1);
		}
	}
}

int main() {
	int k;
	vector<int> S;
	vector<int> result(NUM_LETTERS);
	int tc = 0;
	while (true) {
		cin >> k;
		if (k == 0)
			break;

		//The test cases have to be separated from each other by exactly one blank line. Do not put a blank line after the last test case.
		tc++;
		if (tc > 1)
			cout << endl;

		// S are already sorted in ascending order.
		S.resize(k);
		for (int i = 0; i < k; i++)
			cin >> S[i];

		backtracking(S, result, 0, 0);
	}

	return 0;
}