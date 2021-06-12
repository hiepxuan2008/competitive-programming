// Problem: 191 C. Fools and Roads
// Link: https://codeforces.com/problemset/problem/191/C
// Author: Mai Thanh Hiep
// Complexity: O(N*logN + K*logN), N <= 10^5 is number of cities, K <= 10^5 is number of pairs of fools who visit each other..

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
const int MAX_LOGN = 18; // store 2^17 values
vector<int> graph[MAXN];

int parent[MAXN][MAX_LOGN];
int tin[MAXN], tout[MAXN];
int timer, degree;
int level[MAXN];

ll visitedSum[MAXN];

class LCA { // one-based indexing
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
};

void dfsVisitedSum(int u, int p) {
    for (int v : graph[u]) {
        if (v != p) {
            dfsVisitedSum(v, u);
            visitedSum[u] += visitedSum[v];
        }
    }
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, u, v, k, a, b;
    cin >> n;
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back(make_pair(u, v));
    }
    cin >> k;
    LCA lca;
    lca.build(n, 1); // O(N * logN)
    while (k--) { // O(k * logN)
        cin >> a >> b;
        ++visitedSum[a];
        ++visitedSum[b];
        visitedSum[lca.findLCA(a, b)] -= 2; // O(logN)
    }
    dfsVisitedSum(1, 1);
    for (auto [u, v] : edges) {
        if (level[u] < level[v]) swap(u, v); // Pick u which is has deeper level compared to v
        cout << visitedSum[u] << " ";
    }
    return 0;
}