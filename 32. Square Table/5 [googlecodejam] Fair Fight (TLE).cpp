// Problem: Fair Fight
// Link: https://codingcompetitions.withgoogle.com/codejam/round/0000000000051706/0000000000122838
// Author: Mai Thanh Hiep
// Complexity: O(N^2 * T), Time Limit Exceeded!!

#include <iostream>
#include <unordered_map>
using namespace std;

const int MAXN = 1e5+5;
const int MAX_LOG = 20;

int arr[MAXN][2];
int fMax[2][MAXN][MAX_LOG];
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

int main() {
    ios_base::sync_with_stdio(false);
    int t, n, k;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        cin >> n >> k;

        computeLog2(n);

        for (int i = 0; i < n; ++i) {
            cin >> arr[i][0];
        }
        for (int i = 0; i < n; ++i) {
            cin >> arr[i][1];
        }
        for (int j = 0; j < 2; ++j) {
            computeSparseTable(j, n);
        }

        int ans = 0;
        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                if (abs(queryMax(0, l, r) - queryMax(1, l, r)) <= k) {
                    ans += 1;
                }
            }
        }
        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}