// Problem: 10986 - Sending email
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1927
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <limits.h>

using namespace std;
#define MAX 20000
#define INF 200000001

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

    int N;
    cin >> N;

    int n, m, S, T;
    int s1, s2, w;
    for (int x = 1; x <= N; x++) {
        cin >> n >> m >> S >> T;

        vector<vector<pair<int, int>>> graph(n);
        vector<int> dist(n, INF);

        while (m--) {
            cin >> s1 >> s2 >> w;
            graph[s1].push_back(make_pair(w, s2));
            graph[s2].push_back(make_pair(w, s1));
        }

        dijikstra(S, graph, dist);

        cout << "Case #" << x << ": ";
        if (dist[T] < INF) {
            cout << dist[T] << endl;
        } else {
            cout << "unreachable" << endl;
        }
    }

    return 0;
}
