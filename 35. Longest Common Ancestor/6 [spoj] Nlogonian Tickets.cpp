// Problem: Nlogonian Tickets
// Link: https://www.spoj.com/problems/NTICKETS/
// Author: Mai Thanh Hiep
// Complexity: O(T * (N + Q) * logN)), where T is number of testcases, N <= 10^5 is number of nodes in the tree, Q <= 5*10^5 is number of queries.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;
typedef pair<int, int> pii;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
const int MAX_LOGN = 18; // store 2^17 values
vector<pii> graph[MAXN];

int parent[MAXN][MAX_LOGN];
int tin[MAXN], tout[MAXN];
int timer, degree;

// extra info
int dpMax[MAXN][MAX_LOGN];
int level[MAXN];

class LCA { // one-based indexing
private:
    void dfs(int u, int p, int parentWeight, int depth) {
        tin[u] = ++timer;
        parent[u][0] = p;
        dpMax[u][0] = parentWeight;
        level[u] = depth;
        for (pair<int, int> pair : graph[u]) {
            int w = pair.first, v = pair.second;
            if (v != p) {
                dfs(v, u, w, depth + 1);
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

        // Extra info
        memset(dpMax, 0, sizeof(dpMax));
        memset(level, 0, sizeof(level));
    }
public:
    void build(int n, int root) {
        reset(n);
        dfs(root, root, 0, 0);
        for (int k = 1; k <= degree; ++k) {
            for (int i = 1; i <= n; ++i) {
                parent[i][k] = parent[parent[i][k-1]][k-1];
                dpMax[i][k] = max(dpMax[i][k-1], dpMax[parent[i][k-1]][k-1]);
            }
        }
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
    int getMaxEdgeWhenJumpParent(int u, int steps) {
        int ans = 0;
        while (steps > 0) {
            int k = log2(steps);
            ans = max(ans, dpMax[u][k]);
            u = parent[u][k];
            steps -= 1 << k;
        }
        return ans;
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, t, q;
    LCA lca;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n-1; ++i) {
            cin >> a >> b >> t; // one-based indexing
            graph[a].emplace_back(t, b);
            graph[b].emplace_back(t, a);
        }
        lca.build(n, 1); // O(N*logN)

        cin >> q;
        while (q--) { // O(Q*logN)
            cin >> a >> b; // one-based indexing
            int _lca = lca.findLCA(a, b); // O(logN)
            int maxEdgeFromA = lca.getMaxEdgeWhenJumpParent(a, level[a] - level[_lca]);
            int maxEdgeFromB = lca.getMaxEdgeWhenJumpParent(b, level[b] - level[_lca]);
            cout << max(maxEdgeFromA, maxEdgeFromB) << '\n';
        }
        for (int i = 1; i <= n; ++i) graph[i].clear();
    }
    return 0;
}