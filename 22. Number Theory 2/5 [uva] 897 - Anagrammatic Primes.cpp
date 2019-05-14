// Problem: 897 - Anagrammatic Primes
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=838
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
#define MAXN 999
vector<int> primes;
vector<bool> isPrime;
vector<int> anagrammaticPrimes;
/* Idea:
	-	There is no Anagrammatic Prime in the interval[991, 10000000]. So for any number N >= 991, it would be efficient to print 0.
		Therefore, checking prime upto 1000 is enough for this problem.
*/ 

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
	while (x > 0) {
		digits.push_back(x % 10);
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
	if (n >= MAXN)
		return 0;

	int l = (floor)(log10(n)) + 1;
	if (l == 1)
		l = 10;
	else if (l == 2)
		l = 100;
	else
		l = 1000;

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