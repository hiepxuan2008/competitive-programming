// Problem: 10608 - Friends
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1549
// Auhthor: Mai Thanh Hiep
// Complexity: O(N + MLogN) = O(MLogN)

#include <iostream>
using namespace std;

#define MAX 30000
int parent[MAX];
int sizes[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sizes[i] = 1;
    }
}

int findSet(int u) {
    int oldU = u;
    while (u != parent[u])
        u = parent[u];

    parent[oldU] = u;
    return u;
}

void unionSet(int u, int v) {
    int up = findSet(u);
    int vp = findSet(v);

    if (up != vp) {
        if (sizes[up] > sizes[vp]) {
            parent[vp] = up;
            sizes[up] += sizes[vp];
        } else {
            parent[up] = vp;
            sizes[vp] += sizes[up];
        }
    }
}

int main() {
    int t, n, m;
    cin >> t;

    int a, b;
    while (t--) {
        cin >> n >> m;

        makeSet(n); // O(N)
        for (int i = 0; i < m; i++) { // O(MLogN)
            cin >> a >> b;
            --a, --b;
            unionSet(a, b); // LogN
        }

        int maxFriends = 0;
        for (int i = 0; i < n; i++) { // O(N)
            maxFriends = max(maxFriends, sizes[i]);
        }

        cout << maxFriends << endl;
    }

    return 0;
}
