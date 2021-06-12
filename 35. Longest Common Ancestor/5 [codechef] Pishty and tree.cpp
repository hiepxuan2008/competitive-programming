// Problem: Pishty and tree
// Link: https://www.codechef.com/problems/PSHTTR
// Author: Mai Thanh Hiep
// Complexity: O(T * (N+M) * logN), where T is number of testcases, N <= 10^5 is number of cities, M <= 10^5 is number of queries.
/* Problem: Given a tree with n vertices and wgts on edges,
 *      answer q queries of the form "u graph k" which asks for XOR of all edges wgts on path from 'u' to 'graph'
 *      and has edge weight less than 'k'. In O((n + q)logn)
 * Idea:
 *  - If there was no constraint like 'k' the problem was much easier,
 *      keeping a XOR prefix on euler tour xr_prefix[], answer will be simply xr_prefix[start[u]] ^ xr_prefix[start[graph]],
 *      properties of xor like A^A = 0 and A^0 = A, are helping us here, like the common path from root to u and root to graph i.e.
 *      root to lca(u, graph) will be zeroed by xoring.
 *  - Handling the constraint of 'k' is not that difficult. First point to realize is that queries can be solved offline,
 *      so we are free to solve them in any order and just print them in right order afterwards.
 *      Sorting the queries based on their 'k' makes sense, since for any k we know that edges of wgt less than equal to k are only useful,
 *      hence we should sort edges and update the prefix on euler tree accordingly.
 *      We can keep two pointers, one slides on sorted queries we have answer till now and one which slides on edges that we have updated to our prefix XOR.
 *      Whenever an edges is allowed for further queries, we can update its contribution to the whole subtree of that edges.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

using namespace std;
const int MAXN = 1e5 + 5;

vector<int> graph[MAXN];
int timer;
pair<int, int> edges[MAXN];
int weights[MAXN], tin[MAXN], tout[MAXN];

class BIT {
    vector<int> bit;
public:
    void reset(int n) {
        bit.assign(n+1, 0);
    }
    int get(int id) {
        int ret = 0;
        while (id > 0) {
            ret ^= bit[id];
            id -= id & (-id);
        }
        return ret;
    }
    void update(int id, int val) {
        while (id < bit.size()) {
            bit[id] ^= val;
            id += id & (-id);
        }
    }
    void updateRange(int left, int right, int val) {
        update(left, val);
        update(right+1, val);
    }
};

void dfs(int u, int p) {
    tin[u] = ++timer;
    for (auto v : graph[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer;
}

int ans[MAXN], q1[MAXN], q2[MAXN];

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T, n, u, v, c, k, m;
    cin >> T;
    BIT bit;
    while (T--) {
        cin >> n;
        timer = 0;
        bit.reset(n);
        for (int j = 1; j < n; j++) {
            cin >> u >> v >> c;
            graph[u].push_back(v);
            graph[v].push_back(u);
            edges[j] = {u, v};
            weights[j] = c;
        }
        dfs(1, -1);
        vector<pair<int, int> > sorted;
        for (int i = 1; i < n; i++) {
            if (tin[edges[i].first] < tin[edges[i].second])
                swap(edges[i].first, edges[i].second);
            sorted.emplace_back(weights[i], -edges[i].first);
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> u >> v >> k;
            q1[i] = u, q2[i] = v;
            sorted.emplace_back(k, i);
        }
        sort(sorted.begin(), sorted.end());
        for (auto q : sorted) { // (N+M)*logN
            if (q.second < 0) { // Input edge
                int node = -q.second;
                bit.updateRange(tin[node], tout[node], q.first); // logN
            } else { // Query
                int idx = q.second;
                ans[idx] = bit.get(tin[q1[idx]]) ^ bit.get(tin[q2[idx]]);
            }
        }
        for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
        for (int i = 1; i <= n; i++) graph[i].clear();
    }
}