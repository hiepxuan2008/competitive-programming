// Problem: 1454 F. Array Partition
// Link: https://codeforces.com/problemset/problem/1454/F
// Author: Mai Thanh Hiep
// Complexity: O(T * NlogN), where N <= 2*10^5 is size of array (sum(N) of all testcases <= 2*10^5)

#include <iostream>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 2e5+5;
const int MAX_LOG = 20;

int arr[MAXN];
int fMax[MAXN][MAX_LOG];
int fMin[MAXN][MAX_LOG];
int log_2[MAXN];

void computeSparseTable(int n) { // O(N * logN)
    for (int i = 0; i < n; ++i)
        fMax[i][0] = fMin[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; ++j) {
        int step = 1 << (j - 1);
        for (int i = 0; i + 2 * step <= n; ++i) {
            fMax[i][j] = max(fMax[i][j - 1], fMax[i + step][j - 1]);
            fMin[i][j] = min(fMin[i][j - 1], fMin[i + step][j - 1]);
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
    return max(fMax[l][k], fMax[r - (1 << k) + 1][k]);
}

int queryMin(int l, int r) {
    int k = log_2[r - l + 1];
    return min(fMin[l][k], fMin[r - (1 << k) + 1][k]);
}

bool check(int l, int r, int expected, int n) {
    if (r >= n - 1) return false;
    if (queryMax(r+1, n-1) != expected) return false;
    if (queryMin(l, r) != expected) return false;
    int x = l, y = r - l + 1, z = n - x - y;
    printf("YES\n%d %d %d\n", x, y, z);
    return true;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t, n;
    cin >> t;
    computeLog2(MAXN-1);
    while (t--) { // O(T * N * logN)
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> arr[i];
        computeSparseTable(n); // O(N * logN)
        bool found = false;
        for (int l = 1, r = n - 2; l <= n-2; ++l) { // [0, l), [l, r], (r, n-1] , O(N)
            int maxLeft = queryMax(0, l-1);
            while (r >= l && queryMax(r+1, n-1) <= maxLeft) --r;
            if (r < n-2) ++r;
            if (check(l, r, maxLeft, n) || check(l, r + 1, maxLeft, n)) {
                found = true;
                break;
            }
        }
        if (!found) printf("NO\n");
    }
    return 0;
}