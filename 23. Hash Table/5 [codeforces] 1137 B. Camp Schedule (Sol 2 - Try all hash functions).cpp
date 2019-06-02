// Prolem: 1137 B. Camp Schedule
// Link: https://codeforces.com/problemset/problem/1137/B
// Author: Mai Thanh Hiep
// Complexity: O(MAXN) + O(|S| + O|T|); |S|, |T| <= MAXN = 500000
// Status: ACCEPTED

// Comment: This solution using hash don't make sure 100% correct, but can be ACCEPT with a high probability!

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <limits.h>
using namespace std;

typedef long long ll;
const ll MAXN = 500000;

class HashFunction {
    ll POW[MAXN]; // POW[i] is equal to base^i
    ll hashS[MAXN]; // hashS[i] is hash value from s[0..i]
    int base;
    int MOD;
    string s;

public:
    HashFunction(int base, int mod, const string& s) {
        this->base = base;
        this->MOD = mod;

        // Precompute POW
        POW[0] = 1;
        for (int i = 1; i < MAXN; i++) // O(MAXN)
            POW[i] = (POW[i - 1] * base) % MOD;

        // Precompute hashS
        hashS[0] = s[0] - '0';
        for (int i = 1; i < s.size(); i++) // O(|S|)
            hashS[i] = (hashS[i - 1] * base + s[i] - '0') % MOD;
    }

    ll getHashS(int i, int j) const {
        if (i <= 0)
            return hashS[j];

        return (hashS[j] - hashS[i - 1] * POW[j - i + 1] % MOD + MOD) % MOD;
    }
};

bool isSuffixEqualPrefix(const vector<HashFunction>& hashFunctions, int i, int n) {
    for (int j = 0; j < hashFunctions.size(); j++) {
        if (hashFunctions[j].getHashS(0, i) != hashFunctions[j].getHashS(n - 1 - i, n - 1))
            return false;
    }
    return true;
}

// O(|S|)
int findMaxSuffixAlsoPrefixLength(const string& s) {
    vector<HashFunction> hashFunctions;
    // try all hash functions
    hashFunctions.push_back(HashFunction(2, 1000000003, s));
    hashFunctions.push_back(HashFunction(3, 1000000007, s));
    hashFunctions.push_back(HashFunction(5, 1000000009, s));
    hashFunctions.push_back(HashFunction(11, 1000000009, s));

    int n = s.length();
    int maxLength = 0;
    for (int i = 0; i < n - 1; i++) { // O(|S|)
        if (isSuffixEqualPrefix(hashFunctions, i, n))
            maxLength = i + 1;
    }
    return maxLength;
}

void countZeroAndOne(const string& s, int count[2]) {
    count[0] = count[1] = 0;
    for (int i = 0; i < s.size(); i++) {
        count[s[i] - '0']++;
    }
}

int main() {
    string s, t;
    cin >> s >> t;

    int cntS[2], cntT[2];
    countZeroAndOne(s, cntS);
    countZeroAndOne(t, cntT);

    string ans = "";
    if (cntS[0] >= cntT[0] && cntS[1] >= cntT[1]) {
        // insert t
        ans += t;
        cntS[0] -= cntT[0];
        cntS[1] -= cntT[1];

        // find maxSuffixAlsoPrefixLength
        int maxSuffixAlsoPrefixLength = findMaxSuffixAlsoPrefixLength(t); // O(|T|)
        if (maxSuffixAlsoPrefixLength > 0) {
            t = t.substr(maxSuffixAlsoPrefixLength); // cut prefix of t
        }
        countZeroAndOne(t, cntT); // recount chars need for insert t

        // insert parts of t without prefix
        while (cntS[0] >= cntT[0] && cntS[1] >= cntT[1]) {
            ans += t;
            cntS[0] -= cntT[0];
            cntS[1] -= cntT[1];
        }

        // insert remain chars
        for (int i = 0; i < cntS[0]; i++)
            ans += '0';
        for (int i = 0; i < cntS[1]; i++)
            ans += '1';
    } else {
        ans = s;
    }

    cout << ans;

    return 0;
}