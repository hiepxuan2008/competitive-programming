// Problem: 482 B. Interesting Array
// Link: https://codeforces.com/problemset/problem/482/B
// Author: Mai Thanh Hiep
// Complexity: O(31 * N + 31 * M * logN), where N <= 10^5 is size of array, M <= 10^5 is number of queries

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class UpdateValSegmentTree {
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
    UpdateValSegmentTree(int n) {
        int size = getTreeSize(n);
        segTree.assign(size, 0);
        lazy.assign(size, 0);
    }

    void updatePending(int id, int l, int r) {
        if (lazy[id] == 0) return;
        if (l != r) {
            lazy[leftChildId(id)] = lazy[id];
            lazy[rightChildId(id)] = lazy[id];
        }
        segTree[id] = lazy[id];
        lazy[id] = 0;
    }

    int lazyQuery(int id, int l, int r, int pos) {
        updatePending(id, l, r);
        if (l == r) return segTree[id];
        int m = (l + r) / 2;
        if (pos <= m) return lazyQuery(leftChildId(id), l, m, pos);
        return lazyQuery(rightChildId(id), m + 1, r, pos);
    }

    void lazyUpdate(int id, int l, int r, int fr, int to, int val) {
        updatePending(id, l, r);
        if (fr > r || to < l) return;
        if (fr <= l && r <= to) {
            lazy[id] = val;
            updatePending(id, l, r);
            return;
        }
        int m = (l + r) / 2;
        lazyUpdate(leftChildId(id), l, m, fr, to, val);
        lazyUpdate(rightChildId(id), m + 1, r, fr, to, val);
    }
};

class AndSegmentTree {
private:
    vector<int> segTree;
    int INF_MASK;

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
    AndSegmentTree(int n) {
        int size = getTreeSize(n);
        segTree.assign(size, 0);
        INF_MASK = 0;
        for (int i = 0; i < 32; ++i) INF_MASK |= (1 << i);
    }

    void build(const vector<int>& arr, int id, int l, int r) {
        if (l == r) {
            segTree[id] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, leftChildId(id), l, m);
        build(arr, rightChildId(id), m + 1, r);
        segTree[id] = segTree[leftChildId(id)] & segTree[rightChildId(id)];
    }

    int query(int id, int l, int r, int fr, int to) {
        if (fr > r || to < l) return INF_MASK;
        if (fr <= l && r <= to) return segTree[id];
        int m = (l + r) / 2;
        return query(leftChildId(id), l, m, fr, to) & query(rightChildId(id), m+1, r, fr, to);
    }
};

struct Query {
    int l, r, q;
    Query(int l = 0, int r = 0, int q = 0) : l(l), r(r), q(q) {}
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, r, q;
    cin >> n >> m;
    vector<Query> queries(m);
    vector<UpdateValSegmentTree> segmentTrees;
    for (int i = 0; i < 31; ++i) { // O(31*N)
        segmentTrees.emplace_back(n);
    }
    for (int i = 0; i < m; ++i) { // O(31 * M * logN)
        cin >> l >> r >> q;
        --l; --r;
        queries[i] = {l, r, q};
        for (int j = 0; j < 31; ++j) {
            if ((q >> j) & 1) {
                segmentTrees[j].lazyUpdate(0, 0, n-1, l, r, 1);
            }
        }
    }
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) { // O(31 * M * logN)
        for (int j = 0; j < 31; ++j) {
            if (segmentTrees[j].lazyQuery(0, 0, n-1, i) == 1) {
                arr[i] |= (1 << j);
            }
        }
    }
    AndSegmentTree andSegmentTree(n);
    andSegmentTree.build(arr, 0, 0, n-1); // O(N)
    for (Query& q : queries) { // O(M * logN)
        if (andSegmentTree.query(0, 0, n-1, q.l, q.r) != q.q) {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    return 0;
}