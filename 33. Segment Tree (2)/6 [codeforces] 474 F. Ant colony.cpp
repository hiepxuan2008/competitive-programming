// Problem: 474 F. Ant colony
// Link: https://codeforces.com/problemset/problem/474/F
// Author: Mai Thanh Hiep
// Complexity: O(T * logN + N), where T <= 10^5 is number of testcases, N <= 10^5 is length of array.
/**
 * Problem:
 *      Given array of integer N elements (N <= 10^5, arr[i] <= 10^9).
 *      In a segment (L, R), for each pair of (i, j) between L, R (inclusive), if arr[i] divides arr[j] then points[j] += 1 otherwise points[i] += 1
 *      Let F(L, R) is number indices i between L and R (inclusive), which has points[i] == R - L.
 *      There are total T testcases ( T <= 10^5), each testcase output an answer (R - L + 1 - F(l, r)).
 * Idea:
 *      Comment 1: We see that points[i] == R - L if and only if arr[i] is the divisor of all other numbers (exclusive itself). Or we can understand as
 *          arr[i] is the gcd of all numbers in range [L, R] (include itself).
 *      Comment 2: F(L, R) is number of elements arr[i] in range [L, R], which has arr[i] == gcd of all numbers.
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
int arr[MAXN];

struct Node {
    int gcd;
    int cnt;

    Node(int gcd = 0, int cnt = 0) : gcd(gcd), cnt(cnt) {}
};

Node segTree[4 * MAXN];

Node merge(const Node& A, const Node& B) {
    if (A.gcd == 0) return B;
    if (B.gcd == 0) return A;
    Node res;
    res.gcd = __gcd(A.gcd, B.gcd);
    if (A.gcd == B.gcd) {
        res.cnt = A.cnt + B.cnt;
    } else if (A.gcd == res.gcd) {
        res.cnt = A.cnt;
    } else if (B.gcd == res.gcd) {
        res.cnt = B.cnt;
    } else {
        res.cnt = 0;
    }
    return res;
}

void build(int id, int left, int right) {
    if (left == right) {
        segTree[id] = Node(arr[left], 1);
        return;
    }
    int mid = (left + right) >> 1;
    build(2 * id + 1, left, mid);
    build(2 * id + 2, mid + 1, right);
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
    int n, t, l, r;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    build(0, 0, n-1);
    cin >> t;
    while (t--) { // O(T * logN)
        cin >> l >> r;
        cout << (r - l + 1 - query(0, 0, n - 1, l-1, r-1).cnt) << '\n';
    }
    return 0;
}