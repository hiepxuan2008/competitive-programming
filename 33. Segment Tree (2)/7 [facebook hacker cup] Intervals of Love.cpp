// Problem: Intervals of Love
// Link: https://www.facebook.com/codingcompetitions/hacker-cup/2014/final-round/problems/A
// Author: Mai Thanh Hiep
// Complexity: O(T * M * logN), where T <= 20 is number of testcases, M <= 10^6 is number of queries, N <= 10^6 is length of array.

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;

int arr[MAXN];

struct Node {
    int left, right;
    int longestLeft, longestRight;
    ll cnt;
    Node(int left = 0, int right = 0, int longestLeft = 0, int longestRight = 0, ll cnt = 0LL)
    : left(left), right(right), longestLeft(longestLeft), longestRight(longestRight), cnt(cnt) {}
};

Node segTree[4 * MAXN];

Node merge(const Node& leftNode, const Node& rightNode) {
    if (leftNode.cnt == 0) return rightNode;
    if (rightNode.cnt == 0) return leftNode;

    Node res;
    res.left = leftNode.left;
    res.right = rightNode.right;
    res.longestLeft = leftNode.longestLeft;
    res.longestRight = rightNode.longestRight;
    res.cnt = leftNode.cnt + rightNode.cnt;
    if (arr[leftNode.right] + 1 == arr[rightNode.left]) { // If mid forms a valid slowly increasing subarray
        res.cnt += 1LL * rightNode.longestLeft * leftNode.longestRight;

        if (leftNode.longestLeft == leftNode.right - leftNode.left + 1) {
            res.longestLeft += rightNode.longestLeft;
        }
        if (rightNode.longestRight == rightNode.right - rightNode.left + 1) {
            res.longestRight += leftNode.longestRight;
        }
    }
    return res;
}

void build(int id, int left, int right) {
    if (left > right) return;
    if (left == right) {
        segTree[id] = Node(left, right, 1, 1, 1);
        return;
    }
    int mid = (left + right) >> 1;
    build(2 * id + 1, left, mid);
    build(2 * id + 2, mid + 1, right);
    segTree[id] = merge(segTree[id * 2 + 1], segTree[id * 2 + 2]);
}

void update(int id, int left, int right, int pos) {
    if (left == right) return;
    int mid = (left + right) >> 1;
    if (pos <= mid) {
        update(id * 2 + 1, left, mid, pos);
    } else {
        update(id * 2 + 2, mid + 1, right, pos);
    }
    segTree[id] = merge(segTree[id * 2 + 1], segTree[id * 2 + 2]);
}

Node query(int id, int left, int right, int fr, int to) {
    if (to < left || fr > right) return {};
    if (fr <= left && right <= to) {
        return segTree[id];
    }
    int mid = (left + right) >> 1;
    Node leftRes = query(2 * id + 1, left, mid, fr, to);
    Node rightRes = query(2 * id + 2, mid + 1, right, fr, to);
    return merge(leftRes, rightRes);
}

int main() {
//    fin;
    int T, n, m, op, p, k, l, r;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> arr[i];
        build(0, 0, n - 1); // O(N)

        cin >> m;
        ll ans = 0LL;
        while (m--) { // O(M * logN)
            cin >> op;
            if (op == 0) {
                cin >> p >> k;
                arr[p] = k;
                update(0, 0, n - 1, p); // O(logN)
            } else {
                cin >> l >> r;
                ans += query(0, 0, n-1, l, r).cnt; // O(logN)
            }
        }
        printf("Case #%d: %d\n", tc, (int)(ans % MOD));
    }
    return 0;
}