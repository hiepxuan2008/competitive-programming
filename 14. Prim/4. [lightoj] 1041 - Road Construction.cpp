// Problem: 1041 - Road Construction
// Link: http://lightoj.com/volume_showproblem.php?problem=1041
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

#define INF 1e9
#define MAX 100
using namespace std;

void prim(vector<vector<pair<int, int>>>& graph, int n, int src, vector<int>& dist) {
	vector<int> visited(n, false);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[src] = 0;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		pair<int, int> top = pq.top();
		pq.pop();
		int u = top.second;
		visited[u] = true;

		for (int i = 0; i < graph[u].size(); i++) {
			pair<int, int> neighbor = graph[u][i];
			int v = neighbor.second;
			int w = neighbor.first;

			if (!visited[v] && w < dist[v]) {
				dist[v] = w;
				pq.push(make_pair(w, v));
			}
		}
	}
}

int main() {
	int t;
	cin >> t;

	int m;
	unordered_map<string, int> mapIds;
	string city1, city2;
	int cost, n, idCity1, idCity2;
	for (int c = 1; c <= t; c++) {
		cin >> m;
		n = 0;
		mapIds.clear();

		vector<vector<pair<int, int>>> graph(MAX);
		for (int i = 0; i < m; i++) {
			cin >> city1 >> city2 >> cost;
			if (mapIds.find(city1) == mapIds.end())
				mapIds[city1] = n++;

			if (mapIds.find(city2) == mapIds.end())
				mapIds[city2] = n++;

			idCity1 = mapIds[city1];
			idCity2 = mapIds[city2];

			graph[idCity1].push_back(make_pair(cost, idCity2));
			graph[idCity2].push_back(make_pair(cost, idCity1));
		}

		vector<int> dist(n, INF);
		prim(graph, n, 0, dist);

		int totalCost = 0;
		for (int i = 0; i < n; i++) {
			if (dist[i] == INF) {
				totalCost = -1;
				break;
			}
			totalCost += dist[i];
		}

		cout << "Case " << c << ": ";
		if (totalCost == -1)
			cout << "Impossible" << endl;
		else
			cout << totalCost << endl;
	}

	return 0;
}
