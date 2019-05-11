// Problem: 11060 - Beverages
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2001
// Author: Mai Thanh Hiep
// Complexity: T * O(NLogN + M), N <= 100, M <= 200

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

bool topologicalSort(int V, vector<vector<int>> &graph, vector<int> &result) {
    vector<int> inDegree(V, 0);
    // In the case there is no relation between two beverages Dilbert should start drinking the one that appears first in the input.
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
    int tc = 0;
    while (cin >> n) {
        unordered_map<string, int> mapNameId;
        unordered_map<int, string> mapIdName;
        string str;
        int id = 0;
        for (int i = 0; i < n; i++) {
            cin >> str;
            if (mapNameId.find(str) == mapNameId.end()) {
                mapNameId[str] = id;
                mapIdName[id] = str;
                id++;
            }
        }

        string B1, B2;
        vector<vector<int>> graph(id, vector<int>());
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> B1 >> B2;
            graph[mapNameId[B1]].push_back(mapNameId[B2]); // beverage B2 ​​ has more alcohol than beverage B1
        }

        vector<int> topoOrder;
        bool success = topologicalSort(id, graph, topoOrder); // O(NLogN + M), N <= 100, M <= 200 -> This is complexity of this solution
        
        cout << "Case #" << ++tc << ": Dilbert should drink beverages in this order: ";
        for (int i = 0; i < id - 1; i++) {
            cout << mapIdName[topoOrder[i]] << " ";
        }
        cout << mapIdName[topoOrder[id - 1]] << ".";
        cout << endl << endl;
    }

    return 0;
}