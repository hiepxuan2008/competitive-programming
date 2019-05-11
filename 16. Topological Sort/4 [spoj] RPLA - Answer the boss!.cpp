// Problem: RPLA - Answer the boss!
// Link: https://www.spoj.com/problems/RPLA/
// Author: Mai Thanh Hiep
// Complexity: T * O(N + R + NLogN), N <= 1000, R <= 10000

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Employee {
    int id;
    int rank;
    Employee(int id = 0, int rank = 0) : id(id), rank(rank) {}
};

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

    int T, N, R, R1, R2;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> R;
        vector<vector<int>> graph(N, vector<int>());
        vector<int> inDegree(N, 0);

        while (R--) {
            cin >> R1 >> R2;
            graph[R2].push_back(R1); // R2's rank is higher than R1's rank
            inDegree[R1]++;
        }

        vector<int> topoOrder;
        topologicalSort(N, graph, topoOrder); // O(N + R)
        vector<int> ranks(N, 0);

        for (int u : topoOrder) { // O(N + R)
            if (inDegree[u] == 0) // this is "boss" (not bullied by anybody)
                ranks[u] = 1;

            for (int v : graph[u]) {
                ranks[v] = max(ranks[v], ranks[u] + 1); // rank as low as possible
            }
        }

        vector<Employee> employees(N);
        for (int u = 0; u < N; u++) {
            employees[u] = Employee(u, ranks[u]);
        }

        sort(employees.begin(), employees.end(), [](const Employee& e1, const Employee& e2) { // O(NLogN)
            if (e1.rank == e2.rank) {
                return e1.id < e2.id;
            }
            return e1.rank < e2.rank;
        });

        cout << "Scenario #" << tc << ":" << endl;
        for (int u = 0; u < N; u++) {
            cout << employees[u].rank << " " << employees[u].id << endl;
        }
    }

    return 0;
}
