// Prolem: 514 C. Watto and Mechanism
// Link: http://codeforces.com/contest/514/problem/C
// Author: Mai Thanh Hiep
// Complexity:  O(totaLengthS^2), totaLengthS <= 6*10^5 -> TLE
// Status: Time Limit Exceeded

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;
#define ALPHABET_SIZE 3

bool isMechanismContains(string& s, unordered_set<string>& myset) {
    int len = s.length();
    for (int j = 0; j < len; j++) { // O(|S|^2)
        for (int k = 1; k < ALPHABET_SIZE; k++) {
            s[j] = (s[j] - 'a' + 1) % ALPHABET_SIZE + 'a';
            if (myset.find(s) != myset.end()) // O(|S|) for compute hashcode of S
                return true;
        }

        s[j] = (s[j] - 'a' + 1) % ALPHABET_SIZE + 'a'; // restore to old chars
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    unordered_set<string> myset;
    string s;
    for (int i = 0; i < n; i++) { // O(totalLengthS), totalLengthS <= 6*10^5
        cin >> s;
        myset.insert(s); // O(|S|) for compute hashcode of S
    }

    for (int i = 0; i < m; i++) { // O(totaLengthS^2), totaLengthS <= 6*10^5 -> TLE
        cin >> s;
        cout << (isMechanismContains(s, myset) ? "YES" : "NO") << endl;
    }

    return 0;
}