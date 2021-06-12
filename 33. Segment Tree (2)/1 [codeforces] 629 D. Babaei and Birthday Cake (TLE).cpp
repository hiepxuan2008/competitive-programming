// Problem: 629 D. Babaei and Birthday Cake
// Link: https://codeforces.com/problemset/problem/629/D
// Author: Mai Thanh Hiep
// Complexity: O(N^2), where N <= 10^5 is the number of simple cakes Babaei has. (Time Limit Exceeded)

#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
ll arr[MAXN];
ll dp[MAXN];

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int n, h, r;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> r >> h;
        arr[i] = 1L * h * r * r;
    }
    ll ans = 0;
    // Using Dynamic Programming with Longest Increasing Subsequence idea!!
    for (int i = 0; i < n; ++i) {
        dp[i] = arr[i];
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + arr[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
        ans = max(ans, dp[i]);
    }
    printf("%.6f", M_PI * ans);
    return 0;
}