// Problem: B. Tanya and Postcard
// Link: https://codeforces.com/contest/518/problem/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
	string s, t;
	cin >> s >> t;

    unordered_map<char, int> charCounts;
	char ch;
	for (int i = 0; i < t.size(); i++) {
        ch = t[i];
        charCounts[ch]++;
	}

	int yay = 0;
	for (int i = 0; i < s.size(); i++) {
        ch = s[i];
        if (charCounts[ch] > 0) {
            yay++;
            charCounts[ch]--;
            s[i] = '.';
        }
	}

	int whoops = 0;
	for (int i = 0; i < s.size(); i++) {
        ch = s[i];
        if (ch != '.') {
            if (islower(ch)) {
                if (charCounts[toupper(ch)] > 0) {
                    whoops++;
                    charCounts[toupper(ch)]--;
                }
            } else {
                if (charCounts[tolower(ch)] > 0) {
                    whoops++;
                    charCounts[tolower(ch)]--;
                }
            }
        }
	}

	cout << yay << " " << whoops << endl;

	return 0;
}
