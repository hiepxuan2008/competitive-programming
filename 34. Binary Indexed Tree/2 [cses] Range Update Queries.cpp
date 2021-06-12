// Problem: Range Update Queries
// Link: https://cses.fi/problemset/task/1651
// Author: Mai Thanh Hiep
// Complexity: O((N + Q) * logN), where Q <= 10^5 is number of queries, N <= 10^5 is number of values.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class BIT { // One-based indexing
private:
    vector<ll> bit;
    void update(int id, int val) {
        while (id < bit.size()) {
            bit[id] += val;
            id += id & (-id);
        }
    }
public:
    BIT(int n) {
        bit.resize(n + 1);
    }
    ll get(int id) {
        ll sum = 0;
        while (id > 0) {
            sum += bit[id];
            id -= id & (-id);
        }
        return sum;
    }
    void updateRange(int left, int right, int val) {
        update(left, val);
        update(right + 1, -val);
    }
};


int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, x;
    cin >> n >> q;
    BIT bit(n);
    for (int i = 1; i <= n; ++i) { // O(N * logN)
        cin >> x;
        bit.updateRange(i, i, x);
    }
    int cmd, a, b, u, k;
    while (q--) { // O(Q * logN)
        cin >> cmd;
        if (cmd == 1) {
            cin >> a >> b >> u;
            bit.updateRange(a, b, u);
        } else {
            cin >> k;
            cout << bit.get(k) << '\n';
        }
    }
}