// Problem: SHPATH - The Shortest Path
// Link: https://www.spoj.com/problems/SHPATH/en/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <limits.h>

using namespace std;
#define INF 200001

unordered_map<string, int> mapNameToIndex;

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

    int s, n, p;

    cin >> s;
    int i, j, w;
    string name;

    while (s--) {
        cin >> n;

        vector<vector<pair<int, int>>> graph(n);
        for (i = 0; i < n; i++) {
            cin >> name;
            mapNameToIndex[name] = i;
            cin >> p;

            while (p--) {
                cin >> j >> w;
                --j;
                graph[i].push_back(make_pair(w, j));
            }
        }

        int r;
        cin >> r;
        string src, dst;
        while (r--) {
            cin >> src >> dst;
            vector<int> dist(n, INF);

            int srcIndex = mapNameToIndex[src];
            int dstIndex = mapNameToIndex[dst];
            dijikstra(srcIndex, graph, dist);

            if (dist[dstIndex] < INF) {
                cout << dist[dstIndex] << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }

    return 0;
}
