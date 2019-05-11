// Problem: TOPOSORT - Topological Sorting
// Link: https://www.spoj.com/problems/TOPOSORT/
// Author: Mai Thanh Hiep
// Complexity: O(NLogN + M)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool topologicalSort(int V, vector<vector<int>> &graph, vector<int> &result) {
    vector<int> inDegree(V, 0);
    // If there are multiple solutions print the one, whose first number is smallest, if there are still multiple solutions, print the one whose second number is smallest, and so on.
    priority_queue<int, vector<int>, greater<int>> zeroDegree; // min heap

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
        int u = zeroDegree.top(); zeroDegree.pop();
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
        --x; --y;
        graph[x].push_back(y); // job x needs to be done before job y.
    }

    vector<int> topoOrder;
    bool success = topologicalSort(n, graph, topoOrder); // O(NLogN + M) -> This is complexity of this solution
    if (success) {
        for (int i = 0; i < n; i++)
            cout << (topoOrder[i] + 1) << " ";
        cout << endl;
    } else {
        cout << "Sandro fails." << endl;
    }

    return 0;
}