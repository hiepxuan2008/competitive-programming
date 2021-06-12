// Problem: DRTREE - Dynamically-Rooted Tree
// Link: https://www.spoj.com/problems/DRTREE/
// Author: Mai Thanh Hiep
// Complexity: O(T * (N + Q) * logN)), where T is number of testcases, N <= 10^5 is number of nodes in the tree, Q <= 10^5 is number of queries.
// Idea:
//      Fix the root with 1.
//      If the root is changed to X, we can determine node Y's subtree size as -
//          if X is Y, answer is Sum(N nodes) = Sum[1].
//          if Y is an ancestor of X, answer is Sum[1] — (Y's child's subtree size which contains node X)
//          otherwise, answer is Y's subtree size
//      Reference from: https://codeforces.com/blog/entry/43617

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
const int MAX_LOGN = 18; // store 2^17 values
vector<int> graph[MAXN];
ll weight[MAXN];

int parent[MAXN][MAX_LOGN];
int tin[MAXN], tout[MAXN];
int timer, degree;

// Extra info
ll sum[MAXN];
int level[MAXN];

class LCA { // one-based indexing
private:
    void dfs(int u, int p, int depth) {
        tin[u] = ++timer;
        parent[u][0] = p;
        sum[u] = weight[u];
        level[u] = depth;
        for (int v : graph[u]) {
            if (v != p) {
                dfs(v, u, depth + 1);
                sum[u] += sum[v];
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
    void build(int n, int root) {
        reset(n);
        dfs(root, root, 0);
        for (int k = 1; k <= degree; ++k) {
            for (int i = 1; i <= n; ++i) {
                parent[i][k] = parent[parent[i][k-1]][k-1];
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

    int n, a, b, q;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> weight[i];
    for (int i = 1; i <= n-1; ++i) {
        cin >> a;
        b = i + 1;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    LCA lca;
    lca.build(n, 1); // O(NlogN)

    cin >> q;
    char cmd;
    int currentRoot = 1;
    while (q--) { // O(Q * logN)
        cin >> cmd >> a;
        if (cmd == 'R') {
            currentRoot = a;
        } else {
            if (currentRoot == a) {
                cout << sum[1] << '\n';
                continue;
            }
            int _lca = lca.findLCA(currentRoot, a);
            if (_lca == a) { // if `a` is an ancestor of `currentRoot`,
                int steps = level[currentRoot] - level[a] - 1;
                int node = lca.jumpParent(currentRoot, steps); // jump to child to node `a` (which contains node currentRoot)
                cout << (sum[1] - sum[node]) << '\n';
            }
            else cout << sum[a] << '\n';
        }
    }
    return 0;
}