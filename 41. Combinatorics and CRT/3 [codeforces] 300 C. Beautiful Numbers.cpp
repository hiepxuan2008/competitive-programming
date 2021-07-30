// Problem: 300 C. Beautiful Numbers
// Link: https://codeforces.com/problemset/problem/300/C
// Author: Mai Thanh Hiep
// Complexity: O(N * log10(N)), where N <= 10^6 is number of digits

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class Combinatorics {
    vector<ll> fact;
    vector<ll> factInv;
    int MOD;
    ll fastPow(ll base, int power) { // base^power % MOD
        if (base == 0) return 0;
        if (power == 0) return 1;
        ll res = fastPow(base, power / 2);
        res = (res * res) % MOD;
        if (power & 1)
            res = (res * base) % MOD;
        return res;
    }

    vector<int> getPresentation(int num, int base) {
        vector<int> p;
        while (num > 0) {
            p.push_back(num % base);
            num /= base;
        }
        return p;
    }
public:
    Combinatorics(int mod) {
        this->MOD = mod;
    }

    void computeFactsAndInvFacts(int n) { // fact[i] = i! % MOD
        fact.assign(n + 1, 0);
        factInv.assign(n + 1, 0);

        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        factInv[n] = fastPow(fact[n], MOD - 2);
        for (int i = n - 1; i >= 0; --i) {
            factInv[i] = factInv[i+1] * (i+1) % MOD;
        }
    }

    ll nCkInverseModulo(int n, int k) { // C(n, k) % MOD, it works if and only if n! and MOD are co-prime!
        ll res = fact[n];
        res = (res * factInv[k]) % MOD;
        res = (res * factInv[n - k]) % MOD;
        return res;
    }

    ll nCkInverseModuloForLucas(int n, int k) { // C(n, k) % MOD, it works if and only if n! and MOD are co-prime!
        ll div = fact[n-k] * fact[k] % MOD;
        return fact[n] * fastPow(div, MOD - 2) % MOD;
    }

    ll nCkLucas(int n, int k) { // C(n, k) % MOD, MOD must be a prime number, use it when MOD < n
        vector<int> pN = getPresentation(n, MOD);
        vector<int> pK = getPresentation(k, MOD);
        ll res = 1LL;
        for (int i = 0; i < pK.size(); ++i) {
            res = (res * nCkInverseModuloForLucas(pN[i], pK[i])) % MOD;
        }
        return res;
    }
};

bool containOnlyAorBDigits(int num, int a, int b) { // O(log10(num))
    while (num > 0) {
        int d = num % 10;
        if (d != a && d != b) return false;
        num /= 10;
    }
    return true;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, n, MOD = 1e9 + 7;
    cin >> a >> b >> n;

    Combinatorics combinatorics(MOD);
    combinatorics.computeFactsAndInvFacts(n);

    ll res = 0;
    for (int i = 0; i <= n; ++i) { // Choose i digits `a`, (n-i) digits `b`
        int sumDigits = a * i + (n-i) * b; // sumDigits is at most 9*N
        if (containOnlyAorBDigits(sumDigits, a, b)) { // O(log10(9*N)) ~ O(log10(N))
            res = (res + combinatorics.nCkInverseModulo(n, i)) % MOD;
        }
    }
    cout << res << '\n';

    return 0;
}