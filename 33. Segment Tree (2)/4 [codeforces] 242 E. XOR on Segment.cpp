// Problem: 242 E. XOR on Segment
// Link: https://codeforces.com/problemset/problem/242/E
// Author: Mai Thanh Hiep
// Complexity: O(20 * N + 20 * M * logN), where N <= 10^5 is size of array, M <= 5*10^4 is number of queries
// Idea: XORING a range basically means swapping the count of 1 bits with the count 0 bits for each sub-range
//          in the segment tree if val has 1 bit at that position.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class SumXorSegmentTree {
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
    SumXorSegmentTree(int n) {
        int size = getTreeSize(n);
        segTree.assign(size, 0);
        lazy.assign(size, 0);
    }

    void buildTree(const vector<int>& arr, int bitAt, int id, int l, int r) {
        if (l == r) {
            segTree[id] = (arr[l] >> bitAt) & 1;
            return;
        }
        int m = (l + r) / 2;
        int leftId = leftChildId(id), rightId = rightChildId(id);
        buildTree(arr, bitAt, leftId, l, m);
        buildTree(arr, bitAt, rightId, m+1, r);
        segTree[id] = segTree[leftId] + segTree[rightId];
    }

    void updatePending(int id, int l, int r) {
        if (lazy[id] == 0) return;
        if (l != r) {
            lazy[leftChildId(id)] ^= 1;
            lazy[rightChildId(id)] ^= 1;
        }
        segTree[id] = (r-l+1) - segTree[id];
        lazy[id] = 0;
    }

    int lazyQuery(int id, int l, int r, int fr, int to) {
        updatePending(id, l, r);
        if (fr > r || to < l) return 0;
        if (fr <= l && r <= to) return segTree[id];

        int m = (l + r) / 2;
        return lazyQuery(leftChildId(id), l, m, fr, to) + lazyQuery(rightChildId(id), m + 1, r, fr, to);
    }

    void lazyUpdate(int id, int l, int r, int fr, int to) {
        updatePending(id, l, r);
        if (fr > r || to < l) return;
        if (fr <= l && r <= to) {
            lazy[id] = 1; // update lazy to new value then down
            updatePending(id, l, r);
            return;
        }
        int m = (l + r) / 2;
        lazyUpdate(leftChildId(id), l, m, fr, to);
        lazyUpdate(rightChildId(id), m + 1, r, fr, to);
        segTree[id] = segTree[leftChildId(id)] + segTree[rightChildId(id)];
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    vector<SumXorSegmentTree> segmentTrees;
    for (int i = 0; i < 20; ++i) { // O(20*N)
        segmentTrees.push_back(SumXorSegmentTree(n));
        segmentTrees.back().buildTree(arr, i, 0, 0, n - 1); // O(N)
    }
    int m, t, l, r, x;
    cin >> m;
    while (m-- > 0) {  // O(M * 20*logN)
        cin >> t;
        cin >> l >> r;
        --l; --r; // Convert into 0-based indexing
        if (t == 1) {
            ll ans = 0;
            for (int i = 0; i < 20; ++i) {  // O(20*logN)
                ans += (1LL << i) * segmentTrees[i].lazyQuery(0, 0, n - 1, l, r);
            }
            cout << ans << endl;
        } else if (t == 2) {
            cin >> x;
            for (int i = 0; i < 20; ++i) { // O(20*logN)
                if (((x >> i) & 1) == 1) {
                    segmentTrees[i].lazyUpdate(0, 0, n-1, l, r);
                }
            }
        }
    }
    return 0;
}