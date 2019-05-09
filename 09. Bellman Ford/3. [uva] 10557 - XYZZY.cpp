// Problem: 10557 - XYZZY
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1498
// Solution: Mai Thanh Hiep
// Complextiy: O(N^4), N <= 100

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// check if have path from src to dst
// O(E + V) = O(M + N)
bool bfs(vector<vector<int>>& graph, int n, int src, int dst) {
    vector<bool> visited(n, false);

    queue<int> q;
    q.push(src);
    visited[src] = true;

    int u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            v = graph[u][i];

            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return visited[dst];
}

// O(E*V) = O(M*N), M <= N(N-1)/2 = O(N^2 * N) = O(N^3)
bool bellmanFord(vector<vector<int>>& graph, int n, vector<int>& energy, int s) {
    vector<int> dist(n, -1);
    dist[s] = 100;

	// O(E*V) = O(M*N), M <= N(N-1)/2 = O(N^2 * N) = O(N^3)
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < graph.size(); u++) {
            for (int j = 0; j < graph[u].size(); j++) {
                int v = graph[u][j];
                int w = energy[v];
                // have energy and have better room for energy
                if (dist[u] > 0 && dist[u] + w > dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // can enter to last room
    if (dist[n - 1] >= 0)
        return true;

    // detect positive cycle
	// O(E * (E + V)) = O(M * (M + N)), M <= N(N-1)/2 = O(N^4), N <= 100 -> This is complexity of this solution
    for (int u = 0; u < graph.size(); u++) {
        for (int j = 0; j < graph[u].size(); j++) {
            int v = graph[u][j];
            int w = energy[v];
            if (dist[u] > 0 && dist[u] + w > dist[v]) {
                if (bfs(graph, n, u, n - 1))
                    return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    while (true) {
        cin >> n;
        if (n == -1)
            break;

        vector<int> energy(n);
        vector<vector<int>> graph(n);

        int j;
        for (int i = 0; i < n; i++) {
            cin >> energy[i] >> m;
            while (m--) {
                cin >> j;
                graph[i].push_back(j - 1);
            }
        }

        cout << (bellmanFord(graph, n, energy, 0) ? "winnable" : "hopeless") << endl;
    }
}
