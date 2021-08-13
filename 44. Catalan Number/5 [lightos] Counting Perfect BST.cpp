// Problem: Counting Perfect BST
// Link: https://lightoj.com/problem/counting-perfect-bst
// Author: Mai Thanh Hiep
// Complexity: O(MAX_N log MAX_N + T * logMOD)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const ll MAX_N = 1e5;
const ll MAX_M = 1e10;
const ll MOD = 1e8+7;

vector<ll> fact(3*MAX_N);
vector<ll> ppArr;
void preprocess() {
    fact[0] = 1LL;
    for (int i = 1; i <= fact.size() - 1; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }

    for (ll x = 2; x <= MAX_N; ++x) {
        ll m = x * x;
        while (m <= MAX_M) {
            ppArr.push_back(m);
            m *= x;
        }
    }
    ppArr.push_back(-1);
    sort(ppArr.begin(), ppArr.end());
    ppArr.resize(unique(ppArr.begin(), ppArr.end()) - ppArr.begin());
}

ll fastPow(ll base, int power) { // base^power % MOD
    if (base == 0) return 0;
    if (power == 0) return 1;
    ll res = fastPow(base, power / 2);
    res = (res * res) % MOD;
    if (power & 1)
        res = (res * base) % MOD;
    return res;
}

ll catalan(int n) {
    if (n == 0) return 0LL;
    return fact[2*n] * fastPow(fact[n] * fact[n+1] % MOD, MOD - 2) % MOD;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    preprocess();

    ll t, a, b;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cin >> a >> b;
        int left = lower_bound(ppArr.begin(), ppArr.end(), a) - ppArr.begin(); // Find index of the smallest number >= a
        int right = upper_bound(ppArr.begin(), ppArr.end(), b) - ppArr.begin() - 1; // Find index of the largest number <= b
        cout << "Case " << tc << ": " << catalan(right - left + 1) << endl;
    }

    return 0;
}