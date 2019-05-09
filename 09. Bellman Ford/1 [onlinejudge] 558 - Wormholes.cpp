// Solution: 558 - Wormholes
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=499
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

bool bellmanFord(vector<Edge>& graph, int n, int s) {
    vector<int> dist(n, INF);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c;
    cin >> c;

    int n, m;
    int x, y, t;
    vector<Edge> graph;
    while (c--) {
        graph.clear();

        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> t;
            graph.push_back((Edge){x, y, t});
        }

        bool hasNegativeCycle = bellmanFord(graph, n, 0);
        cout << (hasNegativeCycle ? "possible" : "not possible") << endl;
    }
}
