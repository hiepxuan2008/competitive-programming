// Problem: 1112 - Curious Robin Hood
// Link: http://lightoj.com/volume_showproblem.php?problem=1112
// Author: Mai Thanh Hiep
// Complexity: T * (N + Q * logN), Q <= 50000, N <= 10^5, T <= 5

#include <iostream>
#include <vector>
using namespace std;

int getTreeSize(int n) {
    int size = 1;
    while (size < n) {
        size <<= 1;
    }
    return size << 1;
}

// O(treeSize) ~ O(N)
void buildTree(vector<int>& arr, vector<int>& segtree, int left, int right, int index) {
    if (left == right) {
        segtree[index] = arr[left];
        return;
    }

    int mid = (left + right) / 2;
    buildTree(arr, segtree, left, mid, 2 * index + 1);
    buildTree(arr, segtree, mid + 1, right, 2 * index + 2);
    segtree[index] = segtree[2 * index + 1] + segtree[2 * index + 2];
}

// O(log(treeSize)) ~ O(log(N))
int sumRange(vector<int>& segtree, int left, int right, int from, int to, int index) {
    if (from <= left && right <= to)
        return segtree[index];

    if (from > right || to < left)
        return 0;

    int mid = (left + right) / 2;
    return sumRange(segtree, left, mid, from, to, 2 * index + 1)
        + sumRange(segtree, mid + 1, right, from, to, 2 * index + 2);
}

// O(log(treeSize)) ~ O(log(N))
void updateQuery(vector<int> &segtree, vector<int> &arr, int left, int right, int index, int pos, int value) {
    if (pos < left || right < pos)
        return;

    if (left == right) {
        arr[pos] = value;
        segtree[index] = value;
        return;
    }

    int mid = (left + right) / 2;
    if (pos <= mid)
        updateQuery(segtree, arr, left, mid, 2 * index + 1, pos, value);
    else
        updateQuery(segtree, arr, mid + 1, right, 2 * index + 2, pos, value);

    segtree[index] = segtree[2 * index + 1] + segtree[2 * index + 2];
}

int main() {
    int t;
    scanf("%d", &t);

    int n, q;
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %d", &n, &q);
        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        int treeSize = getTreeSize(n);
        vector<int> segtree(treeSize);
        buildTree(arr, segtree, 0, n - 1, 0); // O(N)

        printf("Case %d:\n", tc);

        int c, i, j, v, temp;
        while (q--) { // O(Q * logN), Q <= 50000, N <= 10^5
            scanf("%d %d", &c, &i);
            switch (c) {
            case 1:
                temp = arr[i];
                updateQuery(segtree, arr, 0, n - 1, 0, i, 0);
                printf("%d\n", temp);
                break;
            case 2:
                scanf("%d", &v);
                updateQuery(segtree, arr, 0, n - 1, 0, i, arr[i] + v);
                break;
            case 3:
                scanf("%d", &j);
                printf("%d\n", sumRange(segtree, 0, n - 1, i, j, 0));
                break;
            }
        }
    }

    return 0;
}