// Problem: Frequent Values
// Link: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176
// Author: Mai Thanh Hiep
// Complexity: O(N + Q), where N <= 10^5 is size of array, Q <= 10^5 is number of queries.

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring> // For memset
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5+5;
const int MAX_LOG = 20;

int arr[MAXN];
int leftIndex[MAXN], rightIndex[MAXN];
int freq[MAXN];
int num[MAXN];

// Those variables is used in RangeMaxQuery class
int log_2[MAXN];
int f[MAXN][MAX_LOG];

class RangeMaxQuery {
private:
    int* arr;
    int n;

public:
    RangeMaxQuery(int* arr, int n) {
        this->arr = arr;
        this->n = n;
    }

    void computeSparseTable() {
        for (int i = 0; i < n; ++i)
            f[i][0] = arr[i];

        for (int j = 1; (1 << j) <= n; ++j) {
            int step = 1 << (j - 1);
            for (int i = 0; i + 2 * step <= n; ++i) {
                f[i][j] = max(f[i][j - 1], f[i + step][j - 1]);
            }
        }
    }

    int queryMax(int l, int r) { // l, r zero-based indexing, inclusive
        if (l > r) return 0;
        int k = log_2[r - l + 1];
        return max(f[l][k], f[r - (1 << k) + 1][k]);
    }
};

void computeLog2(int n) {
    log_2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log_2[i] = log_2[i / 2] + 1;
    }
}

int main() {
//    fin;
//    fout;
    ios_base::sync_with_stdio(false);

    computeLog2(MAXN-1);
    int n, q, l, r;
    while (cin >> n && n) {
        cin >> q;
        int cnt = 0;
        arr[0] = INT_MIN;
        leftIndex[0] = 0;
        memset(freq, 0, sizeof(freq));
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
            num[i] = arr[i] == arr[i - 1] ? cnt : ++cnt;
            freq[cnt - 1]++; // zero-based indexing
            leftIndex[i] = num[i] == num[i - 1] ? leftIndex[i - 1] : i;
        }
        rightIndex[n] = n;
        for (int i = n - 1; i >= 0; --i) {
            rightIndex[i] = num[i] == num[i + 1] ? rightIndex[i + 1] : i;
        }
        RangeMaxQuery rmq(freq, cnt);
        rmq.computeSparseTable();

        while (q-- > 0) {
            cin >> l >> r;  // one-based indexing
            if (num[l] == num[r]) {
                cout << (r-l + 1) << endl;
            } else {
                int cntInLeftBound = rightIndex[l] - l + 1;
                int cntInRightBound = r - leftIndex[r] + 1;
                int leftMiddleIndex = num[l] + 1; // exclude left bound
                int rightMiddleIndex = num[r] - 1; // exclude right bound
                int cntInMiddle = rmq.queryMax(leftMiddleIndex-1, rightMiddleIndex-1);
                cout << max(cntInLeftBound, max(cntInMiddle, cntInRightBound)) << endl;
            }
        }
    }
    return 0;
}