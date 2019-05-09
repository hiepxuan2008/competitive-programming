// Problem: C. Kefa and Park
// Link: https://codeforces.com/problemset/problem/580/C
// Solution: Mai Thanh Hiep
// Complexity: O(V + E) = O(N + N-1) = O(N)

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

#define MAX 100000
bool hasCat[MAX];
vector<vector<int>> graph;
int consecutiveCats[MAX];

void BFS(int src, int n, int m) {
    for (int i = 0; i < n; i++) {
        consecutiveCats[i] = -1;
    }

    queue<int> q;
    q.push(src);
    consecutiveCats[src] = hasCat[src] ? 1 : 0;

    int u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            v = graph[u][i];

            if (consecutiveCats[v] == -1 && (!hasCat[v] || consecutiveCats[u] < m)) {
                if (!hasCat[v]) {
                    consecutiveCats[v] = 0;
                } else {
                    consecutiveCats[v] = consecutiveCats[u] + 1;
                }

                q.push(v);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        hasCat[i] = x == 1;
    }

    graph.resize(n);
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    BFS(0, n, m);

    // browse leafs -> count visited leafs
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (graph[i].size() == 1 // is leaf
            && consecutiveCats[i] != -1) { // is visited
            ans++;
        }
    }

    printf("%d\n", ans);

    return 0;
}
