// Problem: MAKETREE - Hierarchy
// Link: https://www.spoj.com/problems/MAKETREE/
// Author: Mai Thanh Hiep
// Complexity: O(N + K*W), N <= 100000, K < N, W <= 10

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> graph(n, vector<int>());
    int x, y, w;
    for (x = 0; x < k; x++) {
        cin >> w;
        while (w--) {
            cin >> y;
            y--;
            graph[x].push_back(y); // x is superior of y (x is not necessary y's direct boss)
        }
    }

    vector<int> topoOrder;
    bool success = topologicalSort(n, graph, topoOrder); // O(N + K*W), N <= 100000, K < N, W <= 10 -> This is complexity of this solution
    // Therefore, the hierarchy of the company can be represented as a rooted tree.
    // => There are no cycle so success always be true!
    vector<int> boss(n);
    boss[topoOrder[0]] = 0;
    for (int i = 1; i < n; i++) {
        boss[topoOrder[i]] = topoOrder[i - 1] + 1;
    }

    for (int i = 0; i < n; i++) {
        cout << boss[i] << endl;
    }

    return 0;
}
