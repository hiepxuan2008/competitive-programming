// Problem: 7 D. Palindrome Degree
// Link: https://codeforces.com/problemset/problem/1200/E
// Author: Mai Thanh Hiep
// Complexity: O(N), where N is the length of the string does not exceed 5*10^6

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define ll long long

ll BASE = 27;

int main() {
    ios_base::sync_with_stdio(false);

    string str;
    cin >> str;
    ll pow = 1;
    ll hashS = 0, hashRevS = 0;
    int n = str.size();
    vector<int> f(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        hashS = hashS * BASE + str[i];
        hashRevS = hashRevS + str[i] * pow;
        if (hashS == hashRevS) {
            if (i == 0)
                f[i] = 1;
            else
                f[i] = f[(i-1)/2] + 1;
            ans += f[i];
        }
        pow *= BASE;
    }
    cout << ans << endl;
    return 0;
}