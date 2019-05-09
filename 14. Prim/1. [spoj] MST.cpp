// Problem: MST - Minimum Spanning Tree
// Link: https://www.spoj.com/problems/MST/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>

#define INF 1e9
#define MAX 10000
using namespace std;

void prim(vector<vector<pair<int, int>>>& graph, int src, vector<int>& dist) {
	int n = graph.size();
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
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> graph(n);
	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		u--;
		v--;
		graph[u].push_back(make_pair(w, v));
		graph[v].push_back(make_pair(w, u));
	}

	vector<int> dist(n, INF);
	prim(graph, 0, dist);

	long long total = 0;
	for (int i = 0; i < n; i++) {
		total += (long long) dist[i];
	}

	cout << total << endl;

	return 0;
}
