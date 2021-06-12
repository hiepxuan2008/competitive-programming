// Problem: 12238 - Ants Colony
// Link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3390
// Author: Mai Thanh Hiep
// Complexity: O(T * Q*N*logN), where T is number of testcases, N <= 10^5 is number of nodes in the tree, Q <= 10^5 is number of queries. (Time Limit Exceeded!)

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e5 + 5;
const int MAX_LOGN = 18;

vector<pair<ll, int>> graph[MAXN];
unordered_map<int, vector<ll>> cache;
int n;

void dijkstra(int src) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> minHeap;
    minHeap.push(make_pair(0LL, src));
    cache[src] = vector<ll>(n, LONG_MAX);
    vector<ll>& dist = cache[src];
    dist[src] = 0;
    while (minHeap.size() > 0) {
        auto [d, u] = minHeap.top(); minHeap.pop();
        if (d > dist[u]) continue;
        for (auto [w, v] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                minHeap.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int a, l, q, s, t;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n-1; ++i) {
            cin >> a >> l;
            graph[i].emplace_back(l, a);
            graph[a].emplace_back(l, i);
        }
        cin >> q;
        while (q--) {
            cin >> s >> t;
            if (cache.find(s) != cache.end()) {
                cout << cache[s][t] << " ";
            } else if (cache.find(t) != cache.end()) {
                cout << cache[t][s] << " ";
            } else {
                dijkstra(s);
                cout << cache[s][t] << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < n; ++i) graph[i].clear();
        cache.clear();
    }
    return 0;
}