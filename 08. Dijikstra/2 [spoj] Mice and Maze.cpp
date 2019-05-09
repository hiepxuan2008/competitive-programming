// Problem: MICEMAZE - Mice and Maze
// Link: https://www.spoj.com/problems/MICEMAZE/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;
#define MAX 101
#define INF INT_MAX

vector<vector<pair<int, int>>> graph(MAX);
vector<int> dist(MAX, INF);

void dijikstra(int s) {
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
    int n, e, t, m;
    cin >> n >> e >> t >> m;

    int a, b, w;
    while (m--) {
        cin >> a >> b >> w;
        graph[b].push_back(make_pair(w, a)); // reverse path for finding shortest path from end cell to other cells
    }

    dijikstra(e); // finding shortest path from end cell to other cells

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] <= t) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
