// Solution: 106 Miles To Chicago
// Link: https://www.urionlinejudge.com.br/judge/en/problems/view/1655
// Solution: Mai Thanh Hiep
// Summary of problem: Find the longest path of the undirected graph, don't have negative cycle
// Complexity: O(N^2LogN)

#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

#define INF 2
typedef pair<double, int> pdi;

// O(ELogV) = O(MLogN) = O(N^2LogN) -> this complexity of this solution
double dijikstra(const vector<vector<pdi>>& graph, int n, int s) {
    vector<double> dist(n, -INF);
    priority_queue<pdi> pq; // max-heap
    dist[s] = 1;
    pq.push(make_pair(dist[s], s));

    while (!pq.empty()) {
        pdi top = pq.top();
        pq.pop();
        int u = top.second;

        for (int i = 0; i < graph[u].size(); i++) {
            pdi neighbor = graph[u][i];
            int v = neighbor.second;
            double w = neighbor.first;

            if (w * top.first > dist[v]) {
                dist[v] = w * top.first;
                pq.push(make_pair(dist[v], v));
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

		vector<vector<pdi>> graph(n);
		int a, b, p;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> p;
			--a, --b;

			// Each street can be used in both directions
			graph[a].push_back(make_pair(p / 100.0f, b));
			graph[b].push_back(make_pair(p / 100.0f, a));
		}

		cout << fixed << setprecision(6) << (dijikstra(graph, n, 0) * 100.0f) << " percent" << endl;
	}

	return 0;
}
