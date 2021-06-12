// Problem: 380 C. Sereja and Brackets
// Link: https://codeforces.com/problemset/problem/380/C
// Author: Mai Thanh Hiep
// Complexity: O(N + M*logN), where M <= 10^6 is number of queries, N <= 10^5 is length of string (Time Limit Exceeded!)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct Node {
    int ans, open, close;
    Node(int ans = 0, int open = 0, int close = 0) : ans(ans), open(open), close(close) {}
};

class SegmentTree {
private:
    vector<Node> segTree;

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
        segTree.resize(getTreeSize(n));
    }

    void buildTree(const string& str, int id, int l, int r) {
        if (l == r) {
            segTree[id].ans = 0;
            segTree[id].open = str[l] == '(';
            segTree[id].close = str[l] == ')';
            return;
        }
        int m = (l + r) / 2;
        int leftId = leftChildId(id), rightId = rightChildId(id);
        buildTree(str, leftId, l, m);
        buildTree(str, rightId, m+1, r);
        int matched = min(segTree[leftId].open, segTree[rightId].close);
        segTree[id].ans = segTree[leftId].ans + segTree[rightId].ans + matched;
        segTree[id].open = segTree[leftId].open + segTree[rightId].open - matched;
        segTree[id].close = segTree[leftId].close + segTree[rightId].close - matched;
    }

    Node query(int id, int l, int r, int fr, int to) {
        if (fr <= l && r <= to)
            return segTree[id];
        if (fr > r || to < l)
            return Node();
        int m = (l + r) / 2;
        Node leftNode = query(leftChildId(id), l, m, fr, to);
        Node rightNode = query(rightChildId(id), m + 1, r, fr, to);
        int matched = min(leftNode.open, rightNode.close);
        Node res;
        res.ans = leftNode.ans + rightNode.ans + matched;
        res.open = leftNode.open + rightNode.open - matched;
        res.close = leftNode.close + rightNode.close - matched;
        return res;
    }
};


int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int n, m, l, r;
    string str;
    cin >> str;
    n = str.size();
    cin >> m;
    SegmentTree segmentTree(n);
    segmentTree.buildTree(str, 0, 0, n - 1); // O(N)
    while (m-- > 0) { // O(M * logN)
        cin >> l >> r;
        --l;
        --r;
        cout << segmentTree.query(0, 0, n-1, l, r).ans * 2 << endl; // O(logN)
    }
    return 0;
}