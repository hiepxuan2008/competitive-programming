// Problem: 126 B. Password
// Link: https://codeforces.com/problemset/problem/126/B
// Author: Mai Thanh Hiep
// Complexity: O(|s|), |s| <= 10^6

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// O(|p|)
void KMPPreprocess(const string& p, vector<int>& prefix) {
    prefix[0] = 0;
    int m = p.length();
    int j = 0;
    int i = 1;
    while (i < m) {
        if (p[i] == p[j]) {
            j++;
            prefix[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                prefix[i] = 0;
                i++;
            }
        }
    }
}

string solve(const string& s, const vector<int>& prefix) {
    int n = prefix.size();
    int j = prefix[n - 1];
    while (j != 0) {
        for (int i = 1; i < n - 1; i++) {
            if (prefix[i] == j) {
                return s.substr(0, j);
            }
        }
        j = prefix[j - 1];
    }
    return "Just a legend";
}

int main() {
    string s;
    cin >> s;

    vector<int> prefix(s.size());
    KMPPreprocess(s, prefix);

    cout << solve(s, prefix) << endl;

    return 0;
}