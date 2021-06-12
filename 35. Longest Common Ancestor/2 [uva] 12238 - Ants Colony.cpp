// Problem: 12238 - Ants Colony
// Link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3390
// Author: Mai Thanh Hiep
// Complexity: O(T * (N + Q) * logN)), where T is number of testcases, N <= 10^5 is number of nodes in the tree, Q <= 10^5 is number of queries.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
const int MAX_LOGN = 18; // Can store 2^17

vector<pair<int, int>> graph[MAXN];
int parent[MAXN][MAX_LOGN];
int tin[MAXN], tout[MAXN];
int timer, degree;
ll dist[MAXN]; // Extra information

class LCA {
private:
    void dfs(int u, int p) {
        tin[u] = ++timer;
        parent[u][0] = p;
        for (pair<int, int> pair : graph[u]) {
            int w = pair.first, v = pair.second;
            if (v != p) {
                dist[v] = dist[u] + w;
                dfs(v, u);
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
        dist[root] = 0LL;
        dfs(root, root);
        for (int k = 1; k <= degree; ++k) {
            for (int i = 1; i <= n; ++i) {
                parent[i][k] = parent[parent[i][k - 1]][k - 1];
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
};


int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, l, q, s, t;
    LCA lca;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n - 1; ++i) {
            cin >> a >> l;
            graph[i + 1].emplace_back(l, a + 1); // one-based indexing
            graph[a + 1].emplace_back(l, i + 1); // one-based indexing
        }
        lca.build(n, 1); // O(N*logN)
        cin >> q;
        while (q--) { // O(Q*logN)
            cin >> s >> t;
            ++s; ++t; // one-based indexing
            int _lca = lca.findLCA(s, t); // logN
            ll ans = dist[s] + dist[t] - 2LL * dist[_lca];
            cout << ans << " ";
        }
        cout << endl;
        for (int i = 1; i <= n; ++i) graph[i].clear();
    }
    return 0;
}