// Problem: BRCKTS - Brackets
// Link: https://www.spoj.com/problems/BRCKTS/
// Author: Mai Thanh Hiep
// Complexity: Testcase * (N + M * logN); N <= 30000, Testcast = 10

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int left, right;
    Node(int _left = 0, int _right = 0) : left(_left), right(_right) {}
};

int getTreeSize(int n) {
    int size = 1;
    while (size < n) {
        size <<= 1;
    }
    return size << 1;
}

// O(treeSize) ~ O(N)
void buildTree(string& arr, vector<Node>& segtree, int left, int right, int index) {
    if (left == right) {
        if (arr[left] == '(') {
            segtree[index].left = 1;
            segtree[index].right = 0;
        } else {
            segtree[index].left = 0;
            segtree[index].right = 1;
        }
        return;
    }

    int mid = (left + right) / 2;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    buildTree(arr, segtree, left, mid, leftIndex);
    buildTree(arr, segtree, mid + 1, right, rightIndex);

    int matchCount = min(segtree[leftIndex].left, segtree[rightIndex].right);
    segtree[index].left = segtree[leftIndex].left + segtree[rightIndex].left - matchCount;
    segtree[index].right = segtree[leftIndex].right + segtree[rightIndex].right - matchCount;
}

// O(treeSize) ~ O(N)
void updateQueryOppositeBracket(vector<Node> &segtree, string &arr, int left, int right, int index, int pos) {
    if (pos < left || right < pos)
        return;

    if (left == right) {
        if (arr[pos] == '(') {
            arr[pos] = ')';
            segtree[index].left = 0;
            segtree[index].right = 1;
        } else {
            arr[pos] = '(';
            segtree[index].left = 1;
            segtree[index].right = 0;
        }
        return;
    }

    int mid = (left + right) / 2;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    if (pos <= mid)
        updateQueryOppositeBracket(segtree, arr, left, mid, leftIndex, pos);
    else
        updateQueryOppositeBracket(segtree, arr, mid + 1, right, rightIndex, pos);

    int matchCount = min(segtree[leftIndex].left, segtree[rightIndex].right);
    segtree[index].left = segtree[leftIndex].left + segtree[rightIndex].left - matchCount;
    segtree[index].right = segtree[leftIndex].right + segtree[rightIndex].right - matchCount;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    string arr;
    for (int testcase = 1; testcase <= 10; testcase++) {
        cin >> n >> arr >> m;

        int treeSize = getTreeSize(n);
        vector<Node> segtree(treeSize);
        buildTree(arr, segtree, 0, n - 1, 0); // O(N)

        cout << "Test " << testcase << ":" << endl;

        int k;
        while (m--) { // O(M * logN), N <= 30000
            cin >> k;
            if (k == 0) {
                cout << (segtree[0].left == 0 && segtree[0].right == 0 ? "YES" : "NO") << endl;
            } else {
                --k;
                updateQueryOppositeBracket(segtree, arr, 0, n - 1, 0, k);
            }
        }
    }

    return 0;
}