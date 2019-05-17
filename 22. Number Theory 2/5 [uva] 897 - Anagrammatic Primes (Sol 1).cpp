// Problem: 897 - Anagrammatic Primes
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=838
// Author: Mai Thanh Hiep
// Complexity: O(MAXNlog(logMAXN)), MAXN = 10^7
// Status: Accepted!

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
#define MAXN 10000000 // 10^7, n < 10^7 => max of (next power of 10 greater than n) will be 10^7
vector<int> primes;
vector<bool> isPrime;
vector<int> anagrammaticPrimes;

// O(Nlog(logN))
void sievePrimes(int n) {
	primes.clear();
	isPrime.assign(n + 1, true);

	for (int p = 2; p*p <= n; p++) {
		if (isPrime[p]) {
			for (int i = p * p; i <= n; i += p)
				isPrime[i] = false;
		}
	}

	for (int p = 2; p <= n; p++)
		if (isPrime[p])
			primes.push_back(p);
}

bool isAnagrammaticPrimes(int x) {
	vector<int> digits;
	int digit;
	while (x > 0) {
		digit = x % 10;
		if (x >= 10 && (digit % 2 == 0 || digit % 5 == 0)) // This will decrease complexity of algorithm so much!
			return false;

		digits.push_back(digit);
		x = x / 10;
	}

	sort(digits.begin(), digits.end());
	do {
		x = 0;
		for (int i = 0; i < digits.size(); i++)
			x = x * 10 + digits[i];

		if (!isPrime[x])
			return false;
	} while (next_permutation(digits.begin(), digits.end()));

	return true;
}

void sieveAnagrammaticPrimes() {
	for (int i = 0; i < primes.size(); i++) {
		if (isAnagrammaticPrimes(primes[i])) {
			anagrammaticPrimes.push_back(primes[i]);
		}
	}
}

int solve(int n) {
	int l = (floor)(log10(n)) + 1;
	l = pow(10, l);

	for (int i = 0; i < anagrammaticPrimes.size(); i++) {
		if (anagrammaticPrimes[i] > n && anagrammaticPrimes[i] < l) {
			return anagrammaticPrimes[i];
		}
	}
	return 0;
}

int main() {
	sievePrimes(MAXN);
	sieveAnagrammaticPrimes();

	int n;
	while (cin >> n) {
		if (n == 0)
			break;

		cout << solve(n) << endl;
	}

	return 0;
}