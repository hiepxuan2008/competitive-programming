// Problem: 292 E. Copying Data
// Link: https://codeforces.com/problemset/problem/292/E
// Author: Mai Thanh Hiep
// Complexity: O(N + M * logN), where N <= 10^5 is size of array, M <= 10^5 is number of queries

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class SegmentTree {
private:
    vector<int> segTree;
    vector<int> lazy;

    int getTreeSize(int n) {
        int size = 1;
        while (size < n) size <<= 1;
        return size << 1;
    }

    int leftChildId(int i) {
        return i * 2 + 1;
    }

    int rightChildId(int i) {
        return i * 2 + 2;
    }

public:
    SegmentTree(int n) {
        int size = getTreeSize(n);
        segTree.assign(size, 0);
        lazy.assign(size, 0);
    }

    void updatePending(int id, int l, int r) {
        if (lazy[id] == 0) return;
        if (l != r) { // if it has children
            lazy[leftChildId(id)] = lazy[id];
            lazy[rightChildId(id)] = lazy[id];
        }
        segTree[id] = lazy[id];
        lazy[id] = 0;
    }

    int query(int id, int l, int r, int pos) {
        updatePending(id, l, r);
        if (l == r) return segTree[id];
        int m = (l + r) / 2;
        if (pos <= m) return query(leftChildId(id), l, m, pos);
        return query(rightChildId(id), m + 1, r, pos);
    }

    void update(int id, int l, int r, int fr, int to, int val) { // val >= 1
        updatePending(id, l, r);
        if (fr > r || to < l) return;
        if (fr <= l && r <= to) {
            lazy[id] = val;
            updatePending(id, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(leftChildId(id), l, m, fr, to, val);
        update(rightChildId(id), m + 1, r, fr, to, val);
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t, x, y, k;
    cin >> n >> m;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
    SegmentTree segmentTree(n);
    vector<pair<int, int>> q(m+1);
    for (int i = 1; i <= m; ++i) {  // O(M * logN)
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> k; // Copy from A[x:x+k-1] into B[y:y+k-1]
            --x; --y; // convert into zero-based indexing
            q[i].first = x; q[i].second = y;
            segmentTree.update(0, 0, n - 1, y, y + k - 1, i);
        } else if (t == 2) {
            cin >> x;
            --x; // convert into zero-based indexing
            int queryId = segmentTree.query(0, 0, n - 1, x);
            if (queryId == 0) {
                cout << B[x] << '\n';
                continue;
            }
            int dx = x - q[queryId].second;
            cout << A[q[queryId].first + dx] << '\n';
        }
    }
    return 0;
}