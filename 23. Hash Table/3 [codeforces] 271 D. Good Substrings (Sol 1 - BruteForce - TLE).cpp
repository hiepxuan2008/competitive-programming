// Prolem: 271 D. Good Substrings
// Link: http://codeforces.com/problemset/problem/271/D
// Author: Mai Thanh Hiep
// Complexity: 
//			Time:	O(|S|^3), |S| <= 1500
//			Space: 	O(|S|^3), |S| <= 1500 ~ 1500^3=3375000000 bytes > 3GB -> Memory Limit Exceeded
// Status: Memory Limit Exceed or Time Limit Exceeded

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;

	string strBadChars;
	cin >> strBadChars;

	int k;
	cin >> k;

	int n = s.length();
	int badCharCounter = 0;
	unordered_set<string> goodSubStrSet;
	for (int i = 0; i < n; i++) { // O(|S|^3), |S| <= 1500
		badCharCounter = 0;
		for (int j = i; j < n; j++) {
			if (strBadChars[s[j] - 'a'] == '0')
				badCharCounter++;

			if (badCharCounter > k)
				break;

			goodSubStrSet.insert(s.substr(i, j - i + 1)); // O(|S|) -> for calculate hashcode of substr s
		}
	}

	cout << goodSubStrSet.size() << endl;

	return 0;
}