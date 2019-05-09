// Problem: 10048 - Audiophobia
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=989
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e9
using namespace std;

int prim(vector<vector<pair<int, int>>>& graph, int n, int src, int dst) {
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

		// found dst -> return dist
		if (u == dst)
            return dist[u];

		for (int i = 0; i < graph[u].size(); i++) {
			pair<int, int> neighbor = graph[u][i];
			int v = neighbor.second;
			int w = neighbor.first;

			if (!visited[v] && max(w, dist[u]) < dist[v]) {
				dist[v] = max(w, dist[u]);
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	return -1;
}

int main() {
    int _case = 0;
    bool canPrintNewLine = false;
    while (true) {
        int c, s, q;
        cin >> c >> s >> q;

        if (c == 0)
            break;

        if (canPrintNewLine)
            cout << endl;

        vector<vector<pair<int, int>>> graph(c);
        int c1, c2, d;
        for (int i = 0; i < s; i++) {
            cin >> c1 >> c2 >> d;
            --c1;
            --c2;
            graph[c1].push_back(make_pair(d, c2));
            graph[c2].push_back(make_pair(d, c1));
        }

        cout << "Case #" << ++_case << endl;
        for (int i = 0; i < q; i++) {
            cin >> c1 >> c2;
            --c1;
            --c2;
            int res = prim(graph, c, c1, c2);
            if (res == -1)
                cout << "no path" << endl;
            else
                cout << res << endl;
        }

        canPrintNewLine = true;
    }

	return 0;
}
