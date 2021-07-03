// Problem: 482 B. Interesting Array
// Link: https://codeforces.com/problemset/problem/482/B
// Author: Mai Thanh Hiep
// Complexity: O(31*(M+N) + M*logN), where N <= 10^5 is size of array, M <= 10^5 is number of queries

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

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
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, l, r, q;
    cin >> n >> m;
    vector<Query> queries(m);
    for (int i = 0; i < m; ++i) { // O(M`)
        cin >> l >> r >> q;
        --l; --r;
        queries[i] = {l, r, q};
    }
    vector<int> ans(n);
    for (int bitAt = 0; bitAt < 31; ++bitAt) { // O(31 * M + 31 * N)
        vector<int> preSum(n + 1);
        for (Query& q : queries) {
            if ((q.q >> bitAt) & 1) {
                ++preSum[q.l];
                --preSum[q.r + 1];
            }
        }
        for (int i = 0; i < n; ++i) {
            if (preSum[i] > 0) {
                ans[i] |= 1 << bitAt;
            }
            preSum[i + 1] += preSum[i];
        }
    }
    AndSegmentTree andSegmentTree(n);
    andSegmentTree.build(ans, 0, 0, n - 1); // O(N)
    for (Query& q : queries) { // O(M * logN)
        if (andSegmentTree.query(0, 0, n-1, q.l, q.r) != q.q) {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}