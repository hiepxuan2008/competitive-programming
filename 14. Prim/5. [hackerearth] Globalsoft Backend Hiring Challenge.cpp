// Problem: Globalsoft Backend Hiring Challenge
// Link: https://www.hackerearth.com/challenges/hiring/globalsoft-backend-hiring-challenge/algorithm/efficient-network/
// Author: Mai Thanh Hiep
/*
    Find the MST of graph
    Replace long latency cables in MST with short latency cables in available cables
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e9
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
	int n, m;
	int a, b, c;
	cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        --a;
        --b;

        graph[a].push_back(make_pair(c, b));
        graph[b].push_back(make_pair(c, a));
    }
    int q;
    cin >> q;
    vector<int> cables(q);
    for (int i = 0; i < q; i++) {
        cin >> cables[i];
    }

    vector<int> dist(n, INF);
    prim(graph, n, 0, dist);

    sort(dist.begin(), dist.end(), greater<int>()); // sort in decreasing order
    sort(cables.begin(), cables.end()); // sort in increasing order

    long long total = 0;
    for (int i = 0; i < n; i++) {
        if (i < q) {
            total += (long long) min(dist[i], cables[i]);
        } else {
            total += (long long) dist[i];
        }
    }
    cout << total << endl;

	return 0;
}
