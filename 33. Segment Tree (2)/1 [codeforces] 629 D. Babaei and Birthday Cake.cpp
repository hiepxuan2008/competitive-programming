// Problem: 629 D. Babaei and Birthday Cake
// Link: https://codeforces.com/problemset/problem/629/D
// Author: Mai Thanh Hiep
// Complexity: O(NlogN), where N <= 10^5 is the number of simple cakes Babaei has.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const double PI = 3.14159265359;

template<class T>
class MaxSegmentTree {
private:
    vector<T> segTree;
    const int MIN_INF = 0;

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
    MaxSegmentTree(int n) {
        segTree.resize(getTreeSize(n));
    }
    

    T query(int id, int l, int r, int fr, int to) {
        if (fr <= l && r <= to)
            return segTree[id];
        if (fr > r || to < l)
            return MIN_INF;
        int m = (l + r) / 2;
        return max(
                query(leftChildId(id), l, m, fr, to),
                query(rightChildId(id), m + 1, r, fr, to)
        );
    }

    void update(int id, int l, int r, int pos, T val) {
        if (l == r) {
            segTree[id] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) {
            update(leftChildId(id), l, m, pos, val);
        } else {
            update(rightChildId(id), m + 1, r, pos, val);
        }
        segTree[id] = max(segTree[leftChildId(id)], segTree[rightChildId(id)]);
    }
};


bool myComparator(const pli& a, const pli& b) { // Sort by increasing order of Volume and decreasing order of Index
    if (a.first != b.first)
        return a.first < b.first;
    return a.second > b.second;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int n, h, r;
    cin >> n;
    vector<pli> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> r >> h;
        arr[i].first = 1LL * h * r * r;
        arr[i].second = i;
    }
    sort(arr.begin(), arr.end(), myComparator); // O(NlogN)
    MaxSegmentTree<ll> segmentTree(n);
    ll ans = 0;
    for (auto& [v, i] : arr) { // O(NlogN)
        ll tmp = segmentTree.query(0, 0, n - 1, 0, i - 1) + v; // O(logN)
        segmentTree.update(0, 0, n - 1, i, tmp);
        ans = max(ans, tmp);
    }
    printf("%.6f", PI * ans);
    return 0;
}