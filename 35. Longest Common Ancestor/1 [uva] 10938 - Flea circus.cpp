// Problem: 10938 - Flea circus
// Link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1879
// Author: Mai Thanh Hiep
// Complexity: O(T * (N + L) * logN)), where T is number of testcases, N <= 5000 is number of nodes in the tree, L <= 500 is number of queries.

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 5005;
const int MAX_LOGN = 18; // Can store 2^17

vector<int> graph[MAXN];

int parent[MAXN][MAX_LOGN];
int tin[MAXN], tout[MAXN];
int timer, degree;
int level[MAXN]; // Extra information

class LCA {
private:
    void dfs(int u, int p, int depth) {
        tin[u] = ++timer;
        parent[u][0] = p;
        level[u] = depth;
        for (int v : graph[u]) {
            if (v != p) {
                dfs(v, u, depth + 1);
            }
        }
        tout[u] = ++timer;
    }
    
    int isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tin[v] <= tout[u];
    }
    
    void reset(int n) {
        timer = 0;
        degree = ceil(log2(n));
    }
public:
    void build(int n, int root) { // one-based indexing
        reset(n);
        dfs(root, root, 0);
        for (int k = 1; k <= degree; ++k) {
            for (int i = 1; i <= n; ++i) {
                parent[i][k] = parent[parent[i][k-1]][k-1];
            }
        }
    }

    int findLCA(int u, int v) { // one-based indexing
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;

        for (int k = degree; k >= 0; --k) {
            if (!isAncestor(parent[u][k], v)) {
                u = parent[u][k];
            }
        }
        return parent[u][0];
    }

    int jumpParent(int u, int steps) {
        while (steps > 0) {
            int k = log2(steps);
            u = parent[u][k];
            steps -= 1 << k;
        }
        return u;
    }
};


int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, l;
    LCA lca;
    while (cin >> n && n != 0) {
        for (int i = 0; i < n-1; ++i) {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        lca.build(n, 1); // choose any node as root
        cin >> l;
        while (l--) {
            cin >> a >> b;
            int _lca = lca.findLCA(a, b);
            int dist = level[a] + level[b] - level[_lca] * 2;
            int pos;
            if (level[a] > level[b]) {
                pos = lca.jumpParent(a, dist / 2);
            } else {
                pos = lca.jumpParent(b, dist / 2);
            }
            if (dist % 2 == 0) {
                printf("The fleas meet at %d.\n", pos);
            } else {
                printf("The fleas jump forever between %d and %d.\n", min(pos, parent[pos][0]), max(pos, parent[pos][0]));
            }
        }
        for (int i = 1; i <= n; ++i) graph[i].clear();
    }
    return 0;
}