// Prolem: SUFEQPRE - Suffix Equal Prefix
// Link: https://www.spoj.com/problems/SUFEQPRE/
// Author: Mai Thanh Hiep
// Complexity: O(MAXN) + T * O(|S|), |S| <= MAXN = 10^6, T <= 50
// Status: ACCEPTED

// Comment: This solution using hash don't make sure 100% correct, but can be ACCEPT with a high probability!

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
const int base = 29; // base should be a prime number >= number of characters, for example 26 characters in lowercase english
const ll MAXN = 1000000;
ll POW[MAXN]; // POW[i] is equal to base^i
ll hashS[MAXN]; // hashS[i] is hash value from s[0..i]

ll getHashS(int i, int j) {
	if (i <= 0)
		return hashS[j];

	return hashS[j] - hashS[i - 1] * POW[j - i + 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;

	// Precompute POW
	POW[0] = 1;
	for (int i = 1; i < MAXN; i++) // O(MAXN)
		POW[i] = (POW[i - 1] * base);

	string s;
	for (int tc = 1; tc <= t; tc++) {
		cin >> s;

		int n = s.length();

		// Precompute hashS
		hashS[0] = s[0] - 'a';
		for (int i = 1; i < n; i++) // O(|S|)
			hashS[i] = hashS[i - 1] * base + s[i] - 'a';

		int countPrefixAlsoSuffix = 0;
		for (int i = 0; i < n - 1; i++) { // O(|S|)
			if (hashS[i] == getHashS(n - 1 - i, n - 1))
				countPrefixAlsoSuffix++;
		}

		cout << "Case " << tc << ": " << countPrefixAlsoSuffix << endl;
	}

	return 0;
}