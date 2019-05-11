// Author: Mai Thanh Hiep
// Complexity: O(N + M)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int> &result) {
    visited[u] = true;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if (!visited[v]) {
            dfs(v, graph, visited, result);
        }
    }
    result.push_back(u);
}

void topologicalSort(int V, vector<vector<int>> &graph, vector<int> &result) {
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, result);
        }
    }
    reverse(result.begin(), result.end());
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> graph(n, vector<int>());
    
    for (int x, y, i = 0; i < m; i++) {
        cin >> x >> y;
        --x, --y;
        graph[y].push_back(x); // job x needs to be done before job y.
    }
    
    vector<int> result;
    topologicalSort(n, graph, result); // O(N + M) -> This is complexity of this solution
    
    if (result.size() == n) {
        for (int i = 0; i < n; i++)
            cout << result[i] << " ";
        cout << endl;
    } else {
        cout << "Sandro fails." << endl;
    }
    
    return 0;
}
