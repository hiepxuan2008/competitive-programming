// Problem: 52 C. Circular RMQ
// Link: https://codeforces.com/problemset/problem/52/C
// Author: Mai Thanh Hiep
// Complexity: O(N + M * log(N)); N <= 2*10^5, M <= 2*10^5

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits.h>
using namespace std;
typedef long long ll;
#define INF LLONG_MAX;

int getTreeSize(int n) {
    int size = 1;
    while (size < n) {
        size <<= 1;
    }
    return size << 1;
}

// O(treeSize) ~ O(N)
void buildTree(vector<ll>& arr, vector<ll>& segtree, int left, int right, int index) {
    if (left == right) {
        segtree[index] = arr[left];
        return;
    }

    int mid = (left + right) / 2;
    buildTree(arr, segtree, left, mid, 2 * index + 1);
    buildTree(arr, segtree, mid + 1, right, 2 * index + 2);
    segtree[index] = min(segtree[2 * index + 1], segtree[2 * index + 2]);
}

// O(treeSize) ~ O(N)
ll minRange(vector<ll>& segtree, vector<ll>& lazy, int left, int right, int from, int to, int index) {
    if (left > right)
        return INF;

    if (lazy[index] != 0) {
        segtree[index] += lazy[index];
        if (left != right) { // not a leaf node -> have children nodes
            lazy[2 * index + 1] += lazy[index];
            lazy[2 * index + 2] += lazy[index];
        }
        lazy[index] = 0;
    }

    if (from <= left && right <= to)
        return segtree[index];

    if (from > right || to < left)
        return INF;

    int mid = (left + right) / 2;
    return min(
        minRange(segtree, lazy, left, mid, from, to, 2 * index + 1),
        minRange(segtree, lazy, mid + 1, right, from, to, 2 * index + 2)
    );
}

// O(treeSize) ~ O(N)
void updateQueryLazy(vector<ll> &segtree, vector<ll> &lazy, int left, int right, int from, int to, int delta, int index) {
    if (left > right)
        return;

    if (lazy[index] != 0) {
        segtree[index] += lazy[index];
        if (left != right) { // not a leaf node -> have children
            lazy[2 * index + 1] += lazy[index];
            lazy[2 * index + 2] += lazy[index];
        }
        lazy[index] = 0;
    }

    if (from > right || to < left)
        return;

    if (from <= left && right <= to) {
        segtree[index] += delta;
        if (left != right) {
            lazy[2 * index + 1] += delta;
            lazy[2 * index + 2] += delta;
        }
        return;
    }

    int mid = (left + right) / 2;
    updateQueryLazy(segtree, lazy, left, mid, from, to, delta, 2 * index + 1);
    updateQueryLazy(segtree, lazy, mid + 1, right, from, to, delta, 2 * index + 2);

    segtree[index] = min(segtree[2 * index + 1], segtree[2 * index + 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    vector<ll> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int treeSize = getTreeSize(n);
    vector<ll> segtree(treeSize);
    vector<ll> lazy(treeSize, 0);
    buildTree(arr, segtree, 0, n - 1, 0); // O(N)

    string str;
    int x;
    cin >> m;
    cin.ignore(256, '\n');
    while (m--) {  // O(M * logN), N <= 2*10^5, M <= 2*10^5
        getline(cin, str);
        stringstream ss(str);
        vector<int> values;
        while (ss >> x)
            values.push_back(x);

        int l = values[0], r = values[1];

        if (values.size() == 2) {
            if (l <= r) {
                cout << minRange(segtree, lazy, 0, n - 1, l, r, 0) << endl;
            } else {
                ll min1 = minRange(segtree, lazy, 0, n - 1, l, n - 1, 0);
                ll min2 = minRange(segtree, lazy, 0, n - 1, 0, r, 0);
                cout << min(min1, min2) << endl;
            }
        } else {
            int delta = values[2];
            if (l <= r) {
                updateQueryLazy(segtree, lazy, 0, n - 1, l, r, delta, 0);
            } else {
                updateQueryLazy(segtree, lazy, 0, n - 1, l, n - 1, delta, 0);
                updateQueryLazy(segtree, lazy, 0, n - 1, 0, r, delta, 0);
            }
        }
    }

    return 0;
}