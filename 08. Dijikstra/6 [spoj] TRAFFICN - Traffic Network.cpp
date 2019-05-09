// Problem: TRAFFICN - Traffic Network
// Link: https://www.spoj.com/problems/TRAFFICN/en/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <limits.h>

using namespace std;
#define MAX 10001
#define INF 100000*1000 + 1000 + 1 // length of m one-way roads + length of proposed two-way road + 1

void dijikstra(int s, vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, s));
    dist[s] = 0;

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int u = top.second;
        int w = top.first;

        for (int i = 0; i < graph[u].size(); i++) {
            pair<int, int> neighbor = graph[u][i];
            int v = neighbor.second;

            if (w + neighbor.first < dist[v]) {
                dist[v] = w + neighbor.first;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    int n, m, k, s, t;
    int a, b, w;
    while (T--) {
        cin >> n >> m >> k >> s >> t;

        vector<vector<pair<int, int>>> graph(n + 1);
        vector<vector<pair<int, int>>> graph2(n + 1);
        vector<int> dist(n + 1, INF);
        vector<int> dist2(n + 1, INF);

        // one-way road
        while (m--) {
            cin >> a >> b >> w;
            graph[a].push_back(make_pair(w, b)); // for find shortest path from start point to other points
            graph2[b].push_back(make_pair(w, a)); // reverse path for find shortest path from destinate point to other points
        }

        dijikstra(s, graph, dist); // find shortest path from start point to other points
        dijikstra(t, graph2, dist2); // find shortest path from destinate point to other points

        // proposed two-way road
        int ans = INF;
        while (k--) {
            cin >> a >> b >> w;

            // check path: s -> a -> b -> t
            if (dist[a] != INF && dist2[b] != INF) {
                ans = min(ans, dist[a] + w + dist2[b]);
            }

            // check path: s -> b -> a -> t
            if (dist[b] != INF && dist2[a] != INF) {
                ans = min(ans, dist[b] + w + dist2[a]);
            }
        }

        // path from s -> t: don't choose from proposed two-way road
        if (dist[t] != INF)
            ans = min(ans, dist[t]);

        cout << (ans == INF ? -1 : ans) << endl;
    }

    return 0;
}
