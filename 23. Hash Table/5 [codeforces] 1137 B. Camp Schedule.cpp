// Prolem: 1137 B. Camp Schedule
// Link: https://codeforces.com/problemset/problem/1137/B
// Author: Mai Thanh Hiep
// Complexity: O(MAXN) + O(|S| + O|T|); |S|, |T| <= MAXN = 500000
// Status: ACCEPTED

// Comment: This solution using hash don't make sure 100% correct, but can be ACCEPT with a high probability!

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
const int base = 2; // base should be a prime number >= number of characters, for example 2 characters in this binary format
const ll MAXN = 500000;
ll POW[MAXN]; // POW[i] is equal to base^i
ll hashS[MAXN]; // hashS[i] is hash value from s[0..i]

ll getHashS(int i, int j) {
	if (i <= 0)
		return hashS[j];

	return hashS[j] - hashS[i - 1] * POW[j - i + 1];
}


// O(|S|)
int findMaxSuffixAlsoPrefixLength(const string& s) {
	int n = s.length();

	// Precompute hashS
	hashS[0] = s[0] - '0';
	for (int i = 1; i < n; i++) // O(|S|)
		hashS[i] = hashS[i - 1] * base + s[i] - '0';

	int maxLength = 0;
	ll hashPrefix = 0;
	for (int i = 0; i < n - 1; i++) { // O(|S|)
		hashPrefix = hashPrefix * base + s[i] - '0';
		if (hashPrefix == getHashS(n - 1 - i, n - 1))
			maxLength = i + 1;
	}
	return maxLength;
}

void countZeroAndOne(const string& s, int count[2]) {
	count[0] = count[1] = 0;
	for (int i = 0; i < s.size(); i++) {
		count[s[i] - '0']++;
	}
}

int main() {
	// Precompute POW
	POW[0] = 1;
	for (int i = 1; i < MAXN; i++) // O(MAXN)
		POW[i] = (POW[i - 1] * base);

	string s, t;
	cin >> s >> t;

	int cntS[2], cntT[2];
	countZeroAndOne(s, cntS);
	countZeroAndOne(t, cntT);

	string ans = "";
	if (cntS[0] >= cntT[0] && cntS[1] >= cntT[1]) {
		// insert t
		ans += t;
		cntS[0] -= cntT[0];
		cntS[1] -= cntT[1];

		// find maxSuffixAlsoPrefixLength
		int maxSuffixAlsoPrefixLength = findMaxSuffixAlsoPrefixLength(t); // O(|T|)
		if (maxSuffixAlsoPrefixLength > 0) {
			t = t.substr(maxSuffixAlsoPrefixLength); // cut prefix of t
		}
		countZeroAndOne(t, cntT); // recount chars need for insert t

		// insert parts of t without prefix
		while (cntS[0] >= cntT[0] && cntS[1] >= cntT[1]) {
			ans += t;
			cntS[0] -= cntT[0];
			cntS[1] -= cntT[1];
		}

		// insert remain chars
		for (int i = 0; i < cntS[0]; i++)
			ans += '0';
		for (int i = 0; i < cntS[1]; i++)
			ans += '1';
	}
	else {
		ans = s;
	}

	cout << ans;

	return 0;
}