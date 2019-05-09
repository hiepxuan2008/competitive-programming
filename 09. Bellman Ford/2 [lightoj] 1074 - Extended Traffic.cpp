// Solution: 1074 - Extended Traffic
// Link: http://lightoj.com/volume_showproblem.php?problem=1074
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;
#define INF INT_MAX

struct Edge {
    int source;
    int target;
    int weight;
};

bool bellmanFord(vector<Edge>& graph, int n, vector<int>& dist, int s) {
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph.size(); j++) {
            Edge& edge = graph[j];

            int u = edge.source;
            int v = edge.target;
            int w = edge.weight;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
				if (i == n - 1) // detect negative cycle
					return true;
				
                dist[v] = dist[u] + w;
            }
        }
    }
    return false;
}

int cube(int x) {
    return x*x*x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    int n, m, q;
    int src, dst;
    vector<Edge> graph;
    for (int x = 1; x <= T; x++) {
        graph.clear();

        cin >> n;
        vector<int> busyness(n);
        for (int i = 0; i < n; i++) {
            cin >> busyness[i];
        }

        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> src >> dst;
            src--;
            dst--;
            graph.push_back((Edge){src, dst, cube(busyness[dst] - busyness[src])});
        }

        vector<int> dist(n, INF);
        bool hasNegativeCycle = bellmanFord(graph, n, dist, 0);

        cin >> q;

        cout << "Case " << x << ":" << endl;
        for (int i = 0; i < q; i++) {
            cin >> dst;
            dst--;

            if (dist[dst] < 3 || dist[dst] == INF) {
                cout << "?" << endl;
            } else {
                cout << dist[dst] << endl;
            }
        }
    }
}
