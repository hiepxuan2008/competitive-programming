// Problem: 514 D. R2D2 and Droid Army
// Link: https://codeforces.com/problemset/problem/514/D
// Author: Mai Thanh Hiep
// Complexity: O(N*M + N*M*log(N)), where N <= 10^5 is the number of droids, M <= 5 is the number of detail types

#include <iostream>
#include <unordered_map>
using namespace std;

const int MAXN = 1e5+5;
const int MAX_LOG = 20;

int arr[MAXN][5];
int fMax[5][MAXN][MAX_LOG];
int log_2[MAXN];

void computeSparseTable(int type, int n) {
    for (int i = 0; i < n; ++i)
        fMax[type][i][0] = arr[i][type];

    for (int j = 1; (1 << j) <= n; ++j) {
        int step = 1 << (j - 1);
        for (int i = 0; i + 2 * step <= n; ++i) {
            fMax[type][i][j] = max(fMax[type][i][j - 1], fMax[type][i + step][j - 1]);
        }
    }
}

void computeLog2(int n) {
    log_2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log_2[i] = log_2[i / 2] + 1;
    }
}

int queryMax(int type, int l, int r) {
    int k = log_2[r - l + 1];
    return max(fMax[type][l][k], fMax[type][r - (1 << k) + 1][k]);
}

int searchFarthestConsecutiveDestroyDroid(int left, int right, int k, int m) {
    int from = left;
    int ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int totalWeaponsNeed = 0;
        for (int t = 0; t < m; ++t) {
            totalWeaponsNeed += queryMax(t, from, mid);
        }
        if (totalWeaponsNeed <= k) {
            ans = mid; // found a valid answer -> try to expand result in the right side
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
        }
    }
    computeLog2(n);
    for (int t = 0; t < m; ++t) {
        computeSparseTable(t, n);
    }

    int destroyStart = 0;
    int maxLength = 0;
    for (int i = 0; i < n; ++i) {
        int index = searchFarthestConsecutiveDestroyDroid(i, n - 1, k, m);
        if (index == -1) continue; // not found
        int len = index - i + 1;
        if (maxLength < len) {
            maxLength = len;
            destroyStart = i;
        }
    }
    for (int t = 0; t < m; ++t) {
        if (maxLength == 0) cout << 0 << " "; // Not found
        else cout << queryMax(t, destroyStart, destroyStart + maxLength - 1) << " ";
    }
    return 0;
}