// Problem: 12532 - Interval Product
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3977
// Author: Mai Thanh Hiep
// Complexity: Testcase * (N + K * logN); N, K <= 10^5

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

int getSign(int x) {
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return x;
}

// O(treeSize) ~ O(N)
void buildTree(vector<int>& arr, vector<int>& segtree, int left, int right, int index) {
    if (left == right) {
        segtree[index] = getSign(arr[left]);
        return;
    }

    int mid = (left + right) / 2;
    buildTree(arr, segtree, left, mid, 2 * index + 1);
    buildTree(arr, segtree, mid + 1, right, 2 * index + 2);
    segtree[index] = getSign(segtree[2 * index + 1]) * getSign(segtree[2 * index + 2]);
}

// O(treeSize) ~ O(N)
int productRange(vector<int>& segtree, int left, int right, int from, int to, int index) {
    if (from <= left && right <= to)
        return segtree[index];

    if (from > right || to < left)
        return 1;

    int mid = (left + right) / 2;
    return getSign(productRange(segtree, left, mid, from, to, 2 * index + 1))
        * getSign(productRange(segtree, mid + 1, right, from, to, 2 * index + 2));
}

// O(treeSize) ~ O(N)
void updateQuery(vector<int> &segtree, vector<int> &arr, int left, int right, int index, int pos, int value) {
    if (pos < left || right < pos)
        return;

    if (left == right) {
        arr[pos] = getSign(value);
        segtree[index] = getSign(value);
        return;
    }

    int mid = (left + right) / 2;
    if (pos <= mid)
        updateQuery(segtree, arr, left, mid, 2 * index + 1, pos, value);
    else
        updateQuery(segtree, arr, mid + 1, right, 2 * index + 2, pos, value);

    segtree[index] = getSign(segtree[2 * index + 1]) * getSign(segtree[2 * index + 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k) {
        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        int treeSize = getTreeSize(n);
        vector<int> segtree(treeSize);
        buildTree(arr, segtree, 0, n - 1, 0); // O(N)

        char c;
        int i, j, v;
        int ans;
        while (k--) { //  O(K * LogN); N, K <= 10^5
            cin >> c >> i;
            --i;
            switch (c) {
            case 'C':
                cin >> v;
                updateQuery(segtree, arr, 0, n - 1, 0, i, v);
                break;
            case 'P':
                cin >> j;
                --j;
                int ans = productRange(segtree, 0, n - 1, i, j, 0);
                if (ans == 0)
                    cout << '0';
                else if (ans == 1)
                    cout << '+';
                else
                    cout << '-';
                break;
            }
        }
        cout << endl;
    }

    return 0;
}