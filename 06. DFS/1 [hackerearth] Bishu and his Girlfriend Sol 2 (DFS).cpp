// Problem: Bishu and his Girlfriend
// Link: https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/bishu-and-his-girlfriend/
// Solution: Mai Thanh Hiep
// Comment: This is tree graph -> only 1 path between 2 country => So we can use DFS for this problem

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define MAX 1001

vector<vector<int>> graph;
int N, u, v, Q;
int d[MAX];

void DFS(int src) {
    for (int i = 0; i < N; i++) {
        d[i] = -1;
    }

    stack<int> s;
    s.push(src);
    d[src] = 0;
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];

            if (d[v] == -1) {
                d[v] = d[u] + 1;
                s.push(v);
            }
        }
    }
}

int main() {
    scanf("%d", &N);

    graph.resize(N+1);
    for (int i = 0; i < N - 1; i++) {
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    DFS(1);

    scanf("%d", &Q);
    int x;

    int minDist = N; // max distance
    int minDistId = N; // max country id
    for (int i = 0; i < Q; i++) {
        scanf("%d", &x);

        // Have path
        if (d[x] > 0) {
            if (d[x] < minDist) {
                minDist = d[x];
                minDistId = x;
            } else if (d[x] == minDist && x < minDistId) {
                minDistId = x;
            }
        }
    }

    printf("%d\n", minDistId);

    return 0;
}
