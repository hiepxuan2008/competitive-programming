// Author: Mai Thanh Hiep
// Complexity: O(N + M)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool topologicalSort(int V, vector<vector<int>> &graph, vector<int> &result) {
    vector<int> inDegree(V, 0);
    queue<int> zeroDegree;
    
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            inDegree[v]++;
        }
    }
    
    for (int u = 0; u < V; u++) {
        if (inDegree[u] == 0) {
            zeroDegree.push(u);
        }
    }
    
    while (!zeroDegree.empty()) {
        int u = zeroDegree.front(); zeroDegree.pop();
        result.push_back(u);
        for (int v : graph[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                zeroDegree.push(v);
            }
        }
    }

    return result.size() == V;
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
    bool success = topologicalSort(n, graph, result); // O(N + M) -> This is complexity of this solution
    if (success) {
        for (int i = 0; i < n; i++)
            cout << (result[i] + 1) << " ";
        cout << endl;
    } else {
        cout << "Sandro fails." << endl;
    }
    
    return 0;
}
