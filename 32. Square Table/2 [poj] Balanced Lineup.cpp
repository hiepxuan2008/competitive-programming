// Problem: Balanced Lineup
// Link: http://poj.org/problem?id=3264
// Author: Mai Thanh Hiep
// Complexity: O(N + Q), where N is size of array, Q is number of queries

#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1e5+5;
const int MAX_LOG = 20;

int arr[MAXN];
int fMax[MAXN][MAX_LOG];
int fMin[MAXN][MAX_LOG];
int log_2[MAXN];

void computeSparseTable(int n) {
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

int main() {
    ios_base::sync_with_stdio(false);
    int n, q, a, b;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    computeSparseTable(n);
    computeLog2(n);
    while (q-- > 0) {
        cin >> a >> b;
        --a;
        --b;
        cout << (queryMax(a, b) - queryMin(a, b)) << endl;
    }
    return 0;
}