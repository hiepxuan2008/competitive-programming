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
typedef pair<int, int> pii;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class LCA { // one-based indexing
private:
    vector<vector<int>> parent;
    vector<int> tin, tout;
    int timer = 0;
    int degree;

    void dfs(const vector<vector<pii>>& graph, int u, int p) {
        tin[u] = ++timer;
        parent[u][0] = p;
        for (pair<int, int> pair : graph[u]) {
            int w = pair.first, v = pair.second;
            if (v != p) {
                dist[v] = dist[u] + w;
                dfs(graph, v, u);
            }
        }
        tout[u] = ++timer;
    }
    int isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tin[v] <= tout[u];
    }

    void build(const vector<vector<pii>>& graph, int n, int root) {
        dist[root] = 0LL;
        dfs(graph, root, root);
        for (int k = 1; k <= degree; ++k) {
            for (int i = 1; i <= n; ++i) {
                parent[i][k] = parent[parent[i][k-1]][k-1];
            }
        }
    }
public:
    vector<ll> dist; // Extra information

    LCA(const vector<vector<pii>>& graph, int nVertices) {
        int n = nVertices;
        tin.resize(n+1);
        tout.resize(n+1);
        degree = ceil(log2(n));
        timer = 0;
        parent.resize(n+1);
        for (int i = 1; i <= n; ++i) parent[i].resize(degree+1);
        dist.resize(n+1);

        build(graph, nVertices, 1); // choose any node as root
    }

    int findLCA(int u, int v) {
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

    int n, a, l, q, s, t;
    while (cin >> n && n != 0) {
        vector<vector<pii>> graph(n+1);
        for (int i = 1; i <= n-1; ++i) {
            cin >> a >> l;
            graph[i+1].emplace_back(l, a+1); // one-based indexing
            graph[a+1].emplace_back(l, i+1); // one-based indexing
        }
        LCA lca(graph, n); // NlogN
        cin >> q;
        while (q--) { // Q * logN
            cin >> s >> t;
            ++s; ++t; // one-based indexing
            int _lca = lca.findLCA(s, t); // logN
            ll ans = lca.dist[s] + lca.dist[t] - 2LL * lca.dist[_lca];
            cout << ans;
            if (q > 0) cout << " ";
        }
        cout << endl;
    }
    return 0;
}