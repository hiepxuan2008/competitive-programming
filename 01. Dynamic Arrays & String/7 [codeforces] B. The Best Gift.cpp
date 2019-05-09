// Problem: B. The Best Gift
// Link: http://codeforces.com/problemset/problem/609/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long n, m, x;
    scanf("%lld %lld", &n, &m);

    vector<long long> times(m + 1, 0);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        times[x]++;
    }

    long long ans = n * (n - 1) / 2; // total pairs include the pairs that the same genre
    for (int i = 1; i <= m; i++) {
        if (times[i] > 1) { // subtract the pairs that the same genre
            ans -= times[i] * (times[i] - 1) / 2;
        }
    }

    printf("%lld", ans);

    return 0;
}
