// Problem: E. Text Editor
// Link: https://codeforces.com/gym/101466/problem/E
// Author: Mai Thanh Hiep
// Complexity: O(|B| * (|A| + |B|), |B| <= |A| <= 10^5
// Status: Time Limit Exceeded!

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

// O(|s| + |p|)
int KMPSearchCount(const string& t, const string& p, vector<int>& prefix) {
    int n = t.size();
    int m = p.size();
    int i = 0, j = 0;
    int foundCount = 0;
    while (i < n) {
        if (p[j] == t[i]) {
            j++;
            i++;
        }
        if (j == m) {
            foundCount++;
            j = prefix[j - 1];
        } else if (i < n && p[j] != t[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }
    return foundCount;
}

string solve(const string& A, const string& B, int n) {
    string p;
    for (int l = B.size(); l > 0; l--) { // O(|B| * (|A| + |B|), |B| <= |A| <= 10^5 -> TLE
        p = B.substr(0, l);
        vector<int> prefix(p.size());
        KMPPreprocess(p, prefix);
        if (KMPSearchCount(A, p, prefix) >= n) { // O(|A| + |p|)
            return p;
        }
    }
    return "IMPOSSIBLE";
}

int main() {
    string A, B;
    int n;

    getline(cin, A);
    getline(cin, B);
    cin >> n;

    cout << solve(A, B, n) << endl;

    return 0;
}