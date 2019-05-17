// Prolem: SUFEQPRE - Suffix Equal Prefix
// Link: https://www.spoj.com/problems/SUFEQPRE/
// Author: Mai Thanh Hiep
// Complexity: T * O(|S|^2), |S| <= 10^6, T <= 50
// Status: Time Limit Exceeded

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int t;
	cin >> t;

	string s;
	for (int tc = 1; tc <= t; tc++) {
		cin >> s;
		int countPrefixAlsoSuffix = 0;
		for (int i = 1; i < s.length(); i++) { // O(|S|^2)
			if (s.substr(0, i) == s.substr(s.length() - i, i)) {
				countPrefixAlsoSuffix++;
			}
		}

		cout << "Case " << tc << ": " << countPrefixAlsoSuffix << endl;
	}
	return 0;
}