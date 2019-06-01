// Problem: AUSAG - Gaint and Sifat
// Link: https://www.codechef.com/problems/AUSAG
// Author: Mai Thanh Hiep
// Complexity: T * O(|S| + |s|); T <= 30, |s| <= |S| <= 10^5

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

void removeAllSpace(string& s) {
    int n = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ')
            s[n++] = s[i];
    }
    s.resize(n);
}

int main() {
    int t;
    cin >> t;
    cin.ignore(256, '\n');

    string S, s;
    for (int tc = 1; tc <= t; tc++) {
        getline(cin, S);
        getline(cin, s);
        removeAllSpace(S);
        removeAllSpace(s);

        vector<int> prefix(s.size());
        KMPPreprocess(s, prefix);
        cout << "Case " << tc << ": " << KMPSearchCount(S, s, prefix) << endl; // O(|S| + |s|), |s| <= |S| <= 10^5 -> This is complexity of this solution
    }

    return 0;
}