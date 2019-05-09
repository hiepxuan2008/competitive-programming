// Problem: Dhoom 4
// Link: https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/dhoom-4/
// Solution: Mai Thanh Hiep
// Complexity: O(V + E) = O(100000 + N*100000)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define BASE 100000

void BFS(int src, int des, const vector<int> &arr, vector<int> &dist) {
    queue<int> q;
    q.push(src);
    dist[src] = 0;

    int u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        // found shortest path for des
        if (u == des)
            break;

        for (int i = 0; i < arr.size(); i++) {
            v = ((long long)u * arr[i]) % BASE; // a*b can reach to 10^10 -> that's the reason why we cast long long

            // If v is not visited yet
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }

            if (v == des) // found shortest path for des
                return;
        }
    }
}

int solve(int src, int des, const vector<int> &arr) {
    vector<int> dist(BASE);
    for (int i = 0; i < BASE; i++) {
        dist[i] = -1;
    }

    BFS(src, des, arr, dist);

    return dist[des];
}

int main() {
    int initKey, lockKey, otherKeysLength;
    scanf("%d %d", &initKey, &lockKey);
    scanf("%d", &otherKeysLength);

    vector<int> otherKeys(otherKeysLength);
    for (int i = 0; i < otherKeysLength; i++) {
        scanf("%d", &otherKeys[i]);
    }

    printf("%d\n", solve(initKey, lockKey, otherKeys));

    return 0;
}
