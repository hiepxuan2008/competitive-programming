// Problem: FINDSR - Find String Roots
// Link: https://www.spoj.com/problems/FINDSR/
// Author: Mai Thanh Hiep
// Complexity: O(|s|), |s| <= 10^5 -> This is complexity of this solution

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

int solve(vector<int>& prefix) {
    int i = prefix.size() - 1;
    int lastElement = prefix[i];
    int k = lastElement;
    while (prefix[i] == k && k > 0) {
        i--, k--;
    }
    i++;

    if (lastElement % i != 0)
        return 1;

    return lastElement / i + 1;
}

int main() {
    string s;
    while (cin >> s) {
        if (s == "*")
            break;

        vector<int> prefix(s.size());
        KMPPreprocess(s, prefix);  // O(|s|), |s| <= 10^5 -> This is complexity of this solution
        cout << solve(prefix) << endl;
    }

    return 0;
}