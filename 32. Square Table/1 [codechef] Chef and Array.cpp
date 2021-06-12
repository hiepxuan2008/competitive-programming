// Problem: Chef and Array
// Link: https://www.codechef.com/problems/FRMQ
// Author: Mai Thanh Hiep
// Complexity: O(N + M), where N <= 10^5 is size of array, M <= 10^8 is number of queries

#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1e5+5;
const int MAX_LOG = 20;

int arr[MAXN];
int f[MAXN][MAX_LOG];
int log_2[MAXN];

void computeSparseTable(int n) {
    for (int i = 0; i < n; ++i)
        f[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; ++j) {
        int step = 1 << (j - 1);
        for (int i = 0; i + 2 * step <= n; ++i) {
            f[i][j] = max(f[i][j - 1], f[i + step][j - 1]);
        }
    }
}

void computeLog2(int n) {
    log_2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log_2[i] = log_2[i / 2] + 1;
    }
}

int queryMax(int l, int r) {
    int k = log_2[r - l + 1];
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, x, y;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    computeSparseTable(n);
    computeLog2(n);

    cin >> m >> x >> y;
    long long ans = 0;
    while (m-- > 0) {
        ans += queryMax(min(x, y), max(x, y));

        // x = (x + 7) % (n - 1);
        x += 7;
        while (x >= n - 1) x -= (n-1); // -> optimized performance compared to MOD operator

        // y = (y + 11) % n;
        y += 11;
        while (y >= n) y -= n; // -> optimized performance compared to MOD operator
    }
    cout << ans << endl;
    return 0;
}