// Prolem: 514 C. Watto and Mechanism
// Link: http://codeforces.com/contest/514/problem/C
// Author: Mai Thanh Hiep
// Reference from: https://vnoi.info/wiki/algo/string/hash
// Complexity: O(totaLengthS), totaLengthS <= MAXN = 6*10^5
// Status: ACCEPTED

// Comment: This solution using hash don't make sure 100% correct, but can be ACCEPT with a high probability!

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;
#define ALPHABET_SIZE 3

typedef long long ll;
const int base = 3; // base should be a prime number >= number of characters, for example 3 characters 'a', 'b', 'c' in this problem
const ll MAXN = 600000;
ll POW[MAXN]; // POW[i] is equal to base^i

ll computeHashCode(string& s) {
	int n = s.length();
	ll hashCode = 0;
	for (int i = 0; i < n; i++) {
		hashCode = hashCode * base + s[i] - 'a' + 1; // 'a' will be 1, 'b' will be 2 and so on... ('a' start from 1 but 0 to avoid case hash("abc") = hash("bc"))
	}
	return hashCode;
}

bool isMechanismContains(string& s, unordered_set<ll>& hashCodeSet) {
	if (s.length() == 0)
		return false;

	int len = s.length();
	ll originHashCode = computeHashCode(s);
	ll newHashCode;
	char newChar;
	for (int j = 0; j < len; j++) { // O(|S|)
		for (int k = 1; k < ALPHABET_SIZE; k++) {
			newChar = (s[j] - 'a' + k) % ALPHABET_SIZE + 'a';
			newHashCode = originHashCode + POW[len - 1 - j] * (newChar - s[j]);
			if (hashCodeSet.find(newHashCode) != hashCodeSet.end())
				return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	// Precompute POW
	POW[0] = 1;
	for (int i = 1; i < MAXN; i++) // O(MAXN)
		POW[i] = POW[i - 1] * base;

	unordered_set<ll> hashCodeSet;
	string s;
	ll hashCode = 0;
	while (n--) { // O(totalLengthS), totalLengthS <= 6*10^5
		cin >> s;
		hashCode = computeHashCode(s);
		hashCodeSet.insert(hashCode);
	}

	while (m--) { // O(totaLengthS), totaLengthS <= 6*10^5
		cin >> s;

		cout << (isMechanismContains(s, hashCodeSet) ? "YES" : "NO") << endl;
	}

	return 0;
}