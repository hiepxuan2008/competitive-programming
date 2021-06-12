// Problem: 6E Exposition
// Link: https://codeforces.com/problemset/problem/6/E
// Author: Mai Thanh Hiep
// Complexity: O(NlogN), where N <= 10^5 is size of array

#include <iostream>
#include <unordered_map>
#include <vector>
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

int searchPossibleFarthestBook(int left, int right, int k) {
    int from = left;
    int ans = left;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (queryMax(from, mid) - queryMin(from, mid) <= k) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    computeSparseTable(n);
    computeLog2(n);

    int maxBookCnt = 0;
    unordered_map<int, vector<int>> mapCnt2Indices;
    for (int i = 0; i < n; ++i) {
        int index = searchPossibleFarthestBook(i, n - 1, k);
        int bookCnt = index - i + 1;
        mapCnt2Indices[bookCnt].push_back(i);
        maxBookCnt = max(maxBookCnt, bookCnt);
    }
    vector<int> result = mapCnt2Indices[maxBookCnt];
    cout << maxBookCnt << " " << result.size() << endl;
    for (int index : result) {
        cout << (index + 1) << " " << (index + 1 + maxBookCnt - 1) << endl;
    }
    return 0;
}