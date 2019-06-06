// Problem: COINS - Bytelandian gold coins
// Link: https://www.spoj.com/problems/COINS/
// Author: Mai Thanh Hiep

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<int, long long> cache;

long long dp(int n) {
    if (n <= 2)
        return n;

    if (cache.find(n) != cache.end())
        return cache[n];

    cache[n] = max((long long)n, dp(n / 2) + dp(n / 3) + dp(n / 4));
    return cache[n];
}

int main() {
    int n;
    while (cin >> n) {
        cout << dp(n) << endl;
    }

    return 0;
}