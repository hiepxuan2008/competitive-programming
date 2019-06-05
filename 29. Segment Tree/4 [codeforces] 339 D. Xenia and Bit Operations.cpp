// Problem: 339 D. Xenia and Bit Operations
// Link: https://codeforces.com/problemset/problem/339/D
// Author: Mai Thanh Hiep
// Complexity: O(2^N + M * log(2^N)); N <= 17, M <= 10^5

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int getTreeSize(int n) {
    int size = 1;
    while (size < n) {
        size <<= 1;
    }
    return size << 1;
}

// O(treeSize) ~ O(N)
void buildTree(vector<int>& arr, vector<int>& segtree, vector<bool>& isOR, int left, int right, int index) {
    if (left == right) {
        segtree[index] = arr[left];
        isOR[index] = true;
        return;
    }

    int mid = (left + right) / 2;
    buildTree(arr, segtree, isOR, left, mid, 2 * index + 1);
    buildTree(arr, segtree, isOR, mid + 1, right, 2 * index + 2);

    if (isOR[2 * index + 1]) {
        segtree[index] = segtree[2 * index + 1] | segtree[2 * index + 2];
        isOR[index] = false;
    } else {
        segtree[index] = segtree[2 * index + 1] ^ segtree[2 * index + 2];
        isOR[index] = true;
    }
}

// O(treeSize) ~ O(N)
void updateQuery(vector<int> &segtree, const vector<bool>& isOR, vector<int> &arr, int left, int right, int index, int pos, int value) {
    if (pos < left || right < pos)
        return;

    if (left == right) {
        arr[pos] = value;
        segtree[index] = value;
        return;
    }

    int mid = (left + right) / 2;
    if (pos <= mid)
        updateQuery(segtree, isOR, arr, left, mid, 2 * index + 1, pos, value);
    else
        updateQuery(segtree, isOR, arr, mid + 1, right, 2 * index + 2, pos, value);

    if (isOR[2 * index + 1]) {
        segtree[index] = segtree[2 * index + 1] | segtree[2 * index + 2];
    } else {
        segtree[index] = segtree[2 * index + 1] ^ segtree[2 * index + 2];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    n = (int)pow(2, n);
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int treeSize = getTreeSize(n);
    vector<int> segtree(treeSize);
    vector<bool> isOR(treeSize);
    buildTree(arr, segtree, isOR, 0, n - 1, 0); // O(2^N)

    int p, b;
    while (m--) { // O(M * log(2^N)), N <= 17, M <= 10^5
        cin >> p >> b;
        p--;
        updateQuery(segtree, isOR, arr, 0, n - 1, 0, p, b);
        cout << segtree[0] << endl;
    }

    return 0;
}