// Solution: 106 Miles To Chicago
// Link: https://www.urionlinejudge.com.br/judge/en/problems/view/1655
// Solution: Mai Thanh Hiep
// Summary of problem: Find the longest path of the undirected graph, don't have negative cycle
// Complexity: O(N^3)

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Edge {
	int source;
	int target;
	double weight;

	Edge(int _source, int _target, double _weight) : source(_source), target(_target), weight(_weight) {}
};

// O(E*V) = O(M*N) = O(N^2 * N) = O(N^3) -> this complexity of this solution
double bellmanFord(vector<Edge>& graph, int n, int s) {
	vector<double> dist(n, 0);
	dist[s] = 1;

	for (int i = 0; i < n - 1; i++) {
		// for all edges
		for (int j = 0; j < graph.size(); j++) {
			Edge& edge = graph[j];
			int u = edge.source;
			int v = edge.target;
			double w = edge.weight;

			if (dist[u] > 0 && dist[u] * w > dist[v]) {
				dist[v] = dist[u] * w;
			}
		}
	}

	return dist[n - 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	while (true) {
		cin >> n >> m;
		if (n == 0)
			break;

		vector<Edge> graph;
		int a, b, p;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> p;
			--a, --b;
			
			// Each street can be used in both directions
			graph.push_back(Edge( a, b, p / 100.0f ));
			graph.push_back(Edge( b, a, p / 100.0f ));
		}

		cout << fixed << setprecision(6) << (bellmanFord(graph, n, 0) * 100.0f) << " percent" << endl;
	}

	return 0;
}
