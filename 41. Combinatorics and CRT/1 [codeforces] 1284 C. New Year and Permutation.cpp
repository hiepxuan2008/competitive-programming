// Problem: 1284 C. New Year and Permutation
// Link: https://codeforces.com/problemset/problem/1284/C
// Author: Mai Thanh Hiep
// Complexity: O(N), where N <= 250000

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, mod;
    cin >> n >> mod;
    vector<ll> fact(n+1);
    fact[0] = 1LL;
    for (int i = 1; i <= n; ++i)
        fact[i] = fact[i-1] * i % mod;

    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        res += (fact[i] * fact[n-i+1] % mod) * (n-i+1);
        res %= mod;
    }
    cout << res << '\n';
    return 0;
}