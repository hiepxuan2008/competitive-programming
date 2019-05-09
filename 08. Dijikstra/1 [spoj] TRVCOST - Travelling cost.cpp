// Problem: TRVCOST - Travelling cost
// Link: https://www.spoj.com/problems/TRVCOST
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 501
#define INF 50000

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
    int n;
    cin >> n;

    int a, b, w;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> w;
        graph[a].push_back(make_pair(w, b));
        graph[b].push_back(make_pair(w, a));
    }

    int u, q;
    cin >> u >> q;

    dijikstra(u);

    int v;
    for (int i = 0; i < q; i++) {
        cin >> v;
        if (dist[v] == INF) {
            cout << "NO PATH" << endl;
        } else {
            cout << dist[v] << endl;
        }
    }

    return 0;
}
