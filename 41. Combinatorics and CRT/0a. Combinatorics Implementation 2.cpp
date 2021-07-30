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
    vector<ll> _factInv;
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
    Combinatorics(int n, int mod) {
        this->MOD = mod;

        fact.assign(n + 1, 0);
        _factInv.assign(n + 1, -1);

        int minSize = min(n, MOD-1);
        fact[0] = 1;
        for (int i = 1; i <= minSize; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        _factInv[minSize] = fastPow(fact[minSize], MOD - 2);
        for (int i = minSize - 1; i >= 0; --i) {
            _factInv[i] = _factInv[i + 1] * (i + 1) % MOD;
        }
    }

    ll getFactInv(int n) {
        if (_factInv[n] != -1) return _factInv[n];
        return _factInv[n] = fastPow(fact[n], MOD - 2);
    }

    ll nCkInverseModulo(int n, int k) { // C(n, k) % MOD, it works if and only if n! and MOD are co-prime!
        ll res = fact[n];
        res = (res * getFactInv(k)) % MOD;
        res = (res * getFactInv(n-k)) % MOD;
        return res;
    }

    ll nCkLucas(int n, int k) { // C(n, k) % MOD, MOD must be a prime number, use it when MOD < n
        vector<int> pN = getPresentation(n, MOD);
        vector<int> pK = getPresentation(k, MOD);
        ll res = 1LL;
        for (int i = 0; i < pK.size(); ++i) {
            res = (res * nCkInverseModulo(pN[i], pK[i])) % MOD;
        }
        return res;
    }
};

int main() {
    int n = 18, k = 7, mod = 5; // C(n, k) % mod

    Combinatorics combinatorics(n, mod);

    cout << "nCk using inverse modulo: " << combinatorics.nCkInverseModulo(n, k) << "\n"; // Incorrect! Because n! and mod are not co-prime!
    cout << "nCk using Lucas's theorem: " << combinatorics.nCkLucas(n, k) << "\n";
    return 0;
}