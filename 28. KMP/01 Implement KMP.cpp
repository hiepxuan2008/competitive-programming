// Problem: Implement KMP
// Complexity: O(|t| + |p|)

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
void KMPSearch(const string& t, const string& p, vector<int>& prefix) {
    int n = t.size();
    int m = p.size();
    int i = 0, j = 0;
    while (i < n) {
        if (p[j] == t[i]) {
            j++;
            i++;
        }
        if (j == m) {
            cout << "Found pattern at index: " << (i - j) << endl;
            j = prefix[j - 1];
        } else if (i < n && p[j] != t[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
}

int main() {
    string t = "ABABAABACDABABCABAB";
    string p = "ABABCABAB";

    vector<int> prefix(p.size());
    KMPPreprocess(p, prefix);
    KMPSearch(t, p, prefix);

    return 0;
}