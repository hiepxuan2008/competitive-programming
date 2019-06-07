// Problem: 11466 - Largest Prime Divisor
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2461
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
using namespace std;
#define MAX 10000000

// O(Nlog(logN))
void sievePrimes(int n, vector<long long>& primes) {
    vector<bool> prime(n + 1, true);
    for (int p = 2; p*p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int p = 2; p <= n; p++)
        if (prime[p])
            primes.push_back(p);
}

long long largestPrimeDivisor(long long n, const vector<long long>& primes) {
    int countDivisor = 0;
    long long largestDivisor = -1;
    for (int i = 0; primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            while (n % primes[i] == 0)
                n /= primes[i];
            countDivisor++;
            largestDivisor = primes[i];
        }
    }

    if (n > 1) {
        countDivisor++;
        largestDivisor = n;
    }

    if (countDivisor >= 2)
        return largestDivisor;
    return -1;
}

int main() {
    long long n;
    vector<long long> primes;
    sievePrimes(MAX, primes);

    while (cin >> n) {
        if (n == 0)
            break;

        cout << largestPrimeDivisor(abs(n), primes) << endl;
    }

    return 0;
}