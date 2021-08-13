// Topic: Manacher
// Source: BigO Coding Center

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

// Time complexity: O(|S|)
vector<int> manacher(const string &s) {
    int n = s.length();
    vector<int> p(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 0 : min(p[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
            ++k;
        p[i] = --k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return p;
}

int main() {
    string s = "GATACATACCA";
    int n = s.size();
    string t(2 * n + 1, '#');
    for (int i = 0; i < n; ++i)
        t[2 * i + 1] = s[i];

    cout << "String S: " << s << '\n';
    cout << "String T: " << t << '\n';
    cout << "Following are palindrome substrings:\n";
    vector<int> p = manacher(t);
    for (int i = 1; i < p.size() - 1; ++i) {
        if (p[i] > 0) {
            cout << s.substr((i - p[i])/2, p[i]) << '\n';
        }
    }

    return 0;
}