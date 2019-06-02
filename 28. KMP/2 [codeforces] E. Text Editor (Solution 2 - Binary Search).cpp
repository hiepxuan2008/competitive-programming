// Problem: E. Text Editor
// Link: https://codeforces.com/gym/101466/problem/E
// Author: Mai Thanh Hiep
// Complexity: O(log(|B|) * (|A| + |B|), |B| <= |A| <= 10^5
// Comment: 
//          when prefix pattern is short -> more patterns found in document
//          when prefix pattern is long -> less patterns found in document
//          => Apply binary search for finding longest length of prefix that the number of patterns found >= n

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

    int leftLength = 1;
    int rightLength = B.size();
    int midLength;
    int ansLength = 0;
    while (leftLength <= rightLength) { // O(log(|B|) * (|A| + |B|) -> This is complexity of this soluton
        midLength = leftLength + (rightLength - leftLength) / 2;

        p = B.substr(0, midLength);
        vector<int> prefix(p.size());
        KMPPreprocess(p, prefix);
        if (KMPSearchCount(A, p, prefix) >= n) { // O(|A| + |p|)
            ansLength = midLength;
            leftLength = midLength + 1; // try to increase the length of prefix
        } else {
            rightLength = midLength - 1; // try to decrease the length of prefix
        }
    }

    if (ansLength > 0)
        return B.substr(0, ansLength);
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