// Problem: LASTSHOT - THE LAST SHOT
// Link: https://www.spoj.com/problems/LASTSHOT/
// Solution: Mai Thanh Hiep
// Complexity: O(N*(V + E)) = O(N(N + M)) = O(N^2), N max=10000

#include <iostream>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

#define MAX 10000
vector<vector<int>> graph;
bool visited[MAX];

int DFS(int src) {
    stack<int> s;
    s.push(src);
    visited[src] = true;
    int count = 1;

    int u, v;
    while (!s.empty()) {
        u = s.top();
        s.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            v = graph[u][i];

            if (!visited[v]) {
                visited[v] = true;
                s.push(v);
                count++;
            }
        }
    }

    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    graph.resize(n);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        graph[a-1].push_back(b-1);
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        ans = max(DFS(i), ans);
    }

    printf("%d\n", ans);

    return 0;
}
