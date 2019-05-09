// Problem: BENEFACT - The Benefactor
// Link: https://www.spoj.com/problems/BENEFACT/
// Solution: Mai Thanh Hiep
/*
    Summary the problem:
        As you might remember from problem CSTREET in the town the streets are paved in a way that between every two points of interest in the town exactly one paved connection exists.
        -> There are n places and n-1 edges, 2 places have only 1 connection
        => Graph is a tree,

        find the longest distance between 2 places of the city
    Idea:
        Step 1: choose arbitrary source (for simple 0), DFS(0) to other places -> get place that have max distance, called it longestPlace1
        Step 2: choose longestPlace1 as source, DFS(longestPlace1) to others places -> get place that have max distance, called it longestPlace2
        Return dist[longestPlace2]
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;

#define MAX 50000
int dist[MAX];
bool visited[MAX];

int DFS(vector<vector<pair<int, int>>>& graph, int n, int src) {
	memset(dist, 0, n * sizeof(int));
	memset(visited, 0, n * sizeof(bool));

	stack<int> s;
	s.push(src);
	visited[src] = true;

	int u, v, w;
	while (!s.empty()) {
		u = s.top();
		s.pop();

		for (int i = 0; i < graph[u].size(); i++) {
			v = graph[u][i].second;
			w = graph[u][i].first;

			if (!visited[v]) {
				visited[v] = true;
				dist[v] = dist[u] + w;
				s.push(v);
			}
		}
	}

	int maxDistIndex = 0;
	for (int i = 1; i < n; i++)
		if (dist[i] > dist[maxDistIndex])
			maxDistIndex = i;

	return maxDistIndex;
}

int main() {
	int t, n;
	cin >> t;

	while (t--) {
		cin >> n;

		vector<vector<pair<int, int>>> graph(n);
		int a, b, l;
		for (int i = 0; i < n - 1; i++) {
			cin >> a >> b >> l;
			--a;
			--b;

			graph[a].push_back(make_pair(l, b));
			graph[b].push_back(make_pair(l, a));
		}

		int longestPlace1 = DFS(graph, n, 0); // O(N + N + 1)
		int longestPlace2 = DFS(graph, n, longestPlace1); // O(N + N - 1)

		cout << dist[longestPlace2] << endl;
	}

	return 0;
}
