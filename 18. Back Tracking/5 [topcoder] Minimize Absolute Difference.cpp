// Problem: Minimize Absolute Difference
// Author: Mai Thanh Hiep
// Complexity: 

#include <iostream>
#include <vector>
#include <cmath>       /* abs */
using namespace std;

#define N 5
#define N_PARAMS 4

struct Fraction {
	long long numerator, denominator; // avoid overflow 
	Fraction() {}
	Fraction(long long numerator, long long denominator) {
		long long _gcd = gcd(numerator, denominator);
		this->numerator = numerator / _gcd;
		this->denominator = denominator / _gcd;
	}

	long long gcd(long long denom1, long long denom2) {
		long long factor = denom2;
		while (denom2 != 0) {
			factor = denom2;
			denom2 = denom1 % denom2;
			denom1 = factor;
		}
		return denom1;
	}

	bool operator < (const Fraction& obj) {
		return obj.denominator * numerator < denominator * obj.numerator;
	}
};

Fraction f(int xa, int xb, int xc, int xd) {
	return Fraction(abs(xa * xd - xb * xc), xb * xd);
}

bool isExist(const vector<int>& arr, int l, int r, int x) {
	for (int i = l; i <= r; i++)
		if (arr[i] == x)
			return true;

	return false;
}

void backtracking(const vector<int>& arr, int i, vector<int>& pickIndices, vector<int>& bestResult, Fraction& bestScore) {
	if (i == N_PARAMS) {
		Fraction score = f(arr[pickIndices[0]], arr[pickIndices[1]], arr[pickIndices[2]], arr[pickIndices[3]]);
		if (score < bestScore) {
			bestResult = pickIndices;
			bestScore = score;
		}
	} else {
		for (int j = 0; j < N; j++) {
			if (!isExist(pickIndices, 0, i - 1, j)) {
				pickIndices[i] = j;
				backtracking(arr, i + 1, pickIndices, bestResult, bestScore);
			}
		}
	}
}

int main() {
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	vector<int> pickIndices(N_PARAMS);
	vector<int> bestResult(N_PARAMS);
	Fraction bestScore = Fraction(10000, 1);
	backtracking(arr, 0, pickIndices, bestResult, bestScore);

	for (int i = 0; i < bestResult.size(); i++) {
		cout << bestResult[i] << " ";
	}

	return 0;
}