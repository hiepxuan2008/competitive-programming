// Problem: 10600 - ACM Contest and Blackout
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541
// Author: Mai Thanh Hiep
// Summary of the problem: find the first and second MST of the graph
/* Idea:
		Comment: The second MST can't not be first MST

        Use prim to find lowest MST (firstMST)
        secondMST = INF
        for all edges i of MST
            Delete edge i of the MST.
            Run prim again on the entire graph.
            Restore edge i of the MST
            secondMST = min(secondMST, MST)
        return firstMST and secondMST
*/
// Complexity: N * (M * Log(N))

#include <iostream>
#include <vector>
#include <queue>

#define INF 1e9
using namespace std;

// return: -1 if not found, else mst
int prim(vector<vector<pair<int, int>>>& graph, int n, int src, vector<int>& path, vector<vector<bool>>& forbiddenRoad) {
	vector<int> dist(n, INF);
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

			if (!forbiddenRoad[u][v] && !visited[v] && w < dist[v]) {
				dist[v] = w;
				path[v] = u;
				pq.push(make_pair(w, v));
			}
		}
	}

	int total = 0;
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF)
			return -1;

		total += dist[i];
	}
	return total;
}

int main() {
	int t;
	cin >> t;

	int n, m;
	int a, b, c;
	while (t--) {
		cin >> n >> m;

		vector<vector<pair<int, int>>> graph(n);
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> c;
			--a, --b;
			graph[a].push_back(make_pair(c, b));
			graph[b].push_back(make_pair(c, a));
		}

		vector<int> path(n, -1);
		vector<int> path2(n, -1); // unused
		vector<vector<bool>> forbiddenRoad(n, vector<bool>(n, false));

		int firstMST = prim(graph, n, 0, path, forbiddenRoad);
		int secondMST = INF;
		for (int i = 0; i < n; i++) { // for edge in lowest MST
			if (i > 0) {
				forbiddenRoad[i][path[i]] = forbiddenRoad[path[i]][i] = true; // forbid 1 road in MST
				int mst = prim(graph, n, 0, path2, forbiddenRoad);
				if (mst >= 0) // have mst
					secondMST = min(secondMST, mst);

				forbiddenRoad[i][path[i]] = forbiddenRoad[path[i]][i] = false; // restore 1 forbid road in MST
			}
		}

		cout << firstMST << " " << secondMST << endl;
	}

	return 0;
}
