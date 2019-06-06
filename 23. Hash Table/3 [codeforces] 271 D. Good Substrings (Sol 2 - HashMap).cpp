// Prolem: 271 D. Good Substrings
// Link: http://codeforces.com/problemset/problem/271/D
// Author: Mai Thanh Hiep
// Reference from: https://vnoi.info/wiki/algo/string/hash
// Complexity: O(MAXN) + O(|S|^2), |S| <= MAXN = 1500
// Status: ACCEPTED

// Comment: This solution using hash don't make sure 100% correct, but can be ACCEPT with a high probability!

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
const int base = 29; // base should be a prime number >= number of characters, for example 26 characters in lowercase english
const ll MAXN = 1500;
ll POW[MAXN]; // POW[i] is equal to base^i
ll hashS[MAXN]; // hashS[i] is hash value from s[0..i]

ll getHashS(int i, int j) {
    if (i <= 0)
        return hashS[j];

    return hashS[j] - hashS[i - 1] * POW[j - i + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, strBadChars;
    int k;
    cin >> s >> strBadChars >> k;
    int n = s.length();

    // Precompute POW
    POW[0] = 1;
    for (int i = 1; i < MAXN; i++) // O(MAXN)
        POW[i] = POW[i - 1] * base;

    // Precompute hashS
    hashS[0] = s[0] - 'a' + 1; // 'a' will be 1, 'b' will be 2 and so on... ('a' start from 1 but 0 to avoid case hash("abc") = hash("bc"))
    for (int i = 1; i < n; i++)
        hashS[i] = hashS[i - 1] * base + s[i] - 'a' + 1;

    int badCharCounter = 0;
    vector<unordered_set<ll>> goodSubStrHashCodeSet(n + 1);
    int ans = 0, len;
    ll hashCode;
    for (int i = 0; i < n; i++) { // O(|S|^2), |S| <= 1500
        badCharCounter = 0;
        for (int j = i; j < n; j++) {
            if (strBadChars[s[j] - 'a'] == '0')
                badCharCounter++;

            if (badCharCounter > k)
                break;

            len = j - i + 1;
            hashCode = getHashS(i, j);
            if (goodSubStrHashCodeSet[len].find(hashCode) == goodSubStrHashCodeSet[len].end()) {
                ans++;
                goodSubStrHashCodeSet[len].insert(hashCode);
            }
        }
    }

    cout << ans << endl;

    return 0;
}