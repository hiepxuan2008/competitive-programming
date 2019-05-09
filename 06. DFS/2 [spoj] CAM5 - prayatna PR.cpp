// Problem: CAM5 - prayatna PR
// Link: https://www.spoj.com/problems/CAM5
// Solution: Mai Thanh Hiep
// Comment: Bài này tìm vùng số liên thông, không liên quan ngắn dài -> Dùng DFS cũng được

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define MAX 100000

vector<vector<int>> graph;
int N, u, v, Q;
bool visited[MAX];

void DFS(int src) {
    stack<int> s;
    s.push(src);
    visited[src] = true;
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];

            if (!visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &N);
        graph.clear();
        graph.resize(N);

        int e;
        scanf("%d", &e);
        for (int i = 0; i < e; i++) {
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // Update not visited
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                DFS(i);
                ans++;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
