// Problem: 406 - Prime Cuts
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=347
// Author: Mai Thanh Hiep
// Complexity: O(MAXNlog(logMAXN)) + T * O(N), N <= 1000

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1000

// O(Nlog(logN))
void sievePrimes(int n, vector<int>& primes) {
    vector<bool> prime(n + 1, true);
    for (int p = 2; p*p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int p = 1; p <= n; p++) // in this problem, prime numbers include 1
        if (prime[p])
            primes.push_back(p);
}

// O(log(right-left))
int findFirstElementNotGreaterThanX(const vector<int>& arr, int left, int right, int x) {
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if ((arr[mid] == x) || (arr[mid] < x && (mid == right || arr[mid + 1] > x)))
            return mid;
        else if (arr[mid] > x)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int main() {
    vector<int> primes;
    sievePrimes(MAXN, primes); // O(MAXNlog(logMAXN))

    int n, c;
    while (cin >> n) {
        cin >> c;

        int m = findFirstElementNotGreaterThanX(primes, 0, primes.size() - 1, n); // O(Log(primes.size()) = O(Log169)
        m++; // length of prime numbers in range [1, N]

        int len = m % 2 == 1 ? 2 * c - 1 : 2 * c;
        int left = max((m + 1) / 2 - c, 0);
        int right = min(left + len, m); // exclude

        cout << n << " " << c << ":";
        for (int i = left; i < right; i++) { // O(N)
            cout << " " << primes[i];
        }
        cout << endl << endl;
    }

    return 0;
}