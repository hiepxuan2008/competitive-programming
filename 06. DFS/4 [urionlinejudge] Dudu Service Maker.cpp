// Problem: Dudu Service Maker
// Link: https://www.urionlinejudge.com.br/judge/en/problems/view/1610
// Solution: Mai Thanh Hiep
// Summary the problem: Check if there is a cycle in the directed graph using DFS
// Complextiy: O(V + E), V is vertices, E is edges of graph

#include <iostream>
#include <vector>
using namespace std;

#define NOT_VISITED 0
#define CURRENT_VISITED 1
#define OLD_VISITED 2

bool DFS(const vector<vector<int>>& graph, int u, vector<int>& visited) {
	visited[u] = CURRENT_VISITED; // mark as current path

	for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (visited[v] == CURRENT_VISITED) // meet current path -> this is a cycle
            return true;

        if (visited[v] == NOT_VISITED) {
            if (DFS(graph, v, visited))
                return true;
        }
    }

    visited[u] = OLD_VISITED; // mark as old path

    return false;
}

bool isCycle(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> visited(n, NOT_VISITED);
	
    for (int i = 0; i < n; i++) {
        if (visited[i] == NOT_VISITED) {
            if (DFS(graph, i, visited))
                return true;
        }
    }
    return false;
}

int main() {
	int t, n, m;
	cin >> t;

	while (t--) {
		cin >> n >> m;

		vector<vector<int>> graph(n);
		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			--a;
			--b;
			graph[b].push_back(a); // indicating that the document A depends on the document B
		}

		cout << (isCycle(graph) ? "SIM" : "NAO") << endl;
	}

	return 0;
}
