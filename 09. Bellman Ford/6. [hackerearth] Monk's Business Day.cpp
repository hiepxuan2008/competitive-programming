// Solution: Monk's Business Day
// Link: https://www.hackerearth.com/practice/algorithms/graphs/shortest-path-algorithms/practice-problems/algorithm/monks-business-day/description/
// Solution: Mai Thanh Hiep
// Summary of question: Find positive of directed graph
// Idea:
//      Step 1: Reverse sign of weight
//      Step 2: Find the negative of directed graph
// Complexity: O(M*N)

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

// Return: True if exist negative cycle, else return false
bool bellmanFord(vector<Edge>& graph, int n, int s) {
    vector<int> dist(n, INF);
    dist[s] = 0;

	// O(E*V) = O(M*N) -> This is complexity of this solution
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

    int t;
    cin >> t;

    int n, m;
    vector<Edge> graph;
    while (t--) {
        graph.clear();

        cin >> n >> m;
        int i, j, c;
        while (m--) {
            cin >> i >> j >> c;
            --i, --j;
            graph.push_back((Edge){i, j, -c}); // reverse sign of weight
        }

        bool hasNegativeCycle = bellmanFord(graph, n, 0);
        cout << (hasNegativeCycle ? "Yes" : "No") << endl;
    }

    return 0;
}
