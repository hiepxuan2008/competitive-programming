// Topic: Combinatorics Implementation
// Source: BigO Coding Center & Modified by Mai Thanh Hiep

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

int main() {
    int n = 18, k = 7, mod = 5; // C(n, k) % mod

    Combinatorics combinatorics(mod);
    combinatorics.computeFactsAndInvFacts(n);

    cout << "nCk using inverse modulo: " << combinatorics.nCkInverseModulo(n, k) << "\n"; // Incorrect! Because n! and mod are not co-prime!
    cout << "nCk using Lucas's theorem: " << combinatorics.nCkLucas(n, k) << "\n";
    return 0;
}