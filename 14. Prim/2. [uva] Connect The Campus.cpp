// Problem: 10397 - Connect the Campus
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1338
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>
#include <math.h>

#define INF 1e9
#define MAX 750
using namespace std;

void prim(vector<vector<pair<double, int>>>& graph, int src, vector<double>& dist) {
	int n = graph.size();
	vector<bool> visited(n, false);

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	dist[src] = 0;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		pair<double, int> top = pq.top();
		pq.pop();
		int u = top.second;
		visited[u] = true;

		for (int i = 0; i < graph[u].size(); i++) {
			pair<double, int> neighbor = graph[u][i];
			int v = neighbor.second;
			double w = neighbor.first;

			if (!visited[v] && w < dist[v]) {
				dist[v] = w;
				pq.push(make_pair(w, v));
			}
		}
	}
}

double calcDistance(pair<int, int>& p1, pair<int, int>& p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

int main() {
    int n;
    while (cin >> n) {
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].first >> points[i].second;
        }

        vector<vector<pair<double, int>>> graph(n);
        double buildingDistances[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double w = calcDistance(points[i], points[j]);
                buildingDistances[i][j] = w;
            }
        }

        int m, u, v;
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            u--;
            v--;
            buildingDistances[u][v] = buildingDistances[v][u] = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double w = buildingDistances[i][j];
                graph[i].push_back(make_pair(w, j));
                graph[j].push_back(make_pair(w, i));
            }
        }

        vector<double> dist(n, INF);
        prim(graph, 0, dist);

        double total = 0;
        for (int i = 0; i < n; i++) {
            total += dist[i];
        }

        printf("%0.2f\n", total);
    }

	return 0;
}
