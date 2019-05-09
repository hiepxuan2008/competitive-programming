// Problem: ARBITRAG - Arbitrage
// Link: https://www.spoj.com/problems/ARBITRAG/
// Author: Mai Thanh Hiep
// Complexity: O(N^3), N <= 30

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool floydWarshall(vector<vector<double>>& dist, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] > 0 && dist[k][j] > 0 && dist[i][j] < dist[i][k] * dist[k][j]) {
                    dist[i][j] = dist[i][k] * dist[k][j];
                }
            }
        }
    }

    // check positive cycle
    for (int i = 0; i < V; i++) {
        if (dist[i][i] > 1)
            return true;
    }
    return false;
}

int main() {
    int T = 0;
    int n, m;
    string s, s1, s2;
    int id1, id2;
    double convertRate;
    while (true) {
        cin >> n;
        if (n == 0)
            break;

        vector<vector<double>> dist(n, vector<double>(n));
        unordered_map<string, int> mapIds;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    dist[i][j] = 1;
                } else {
                    dist[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            cin >> s;
            mapIds[s] = i;
        }

        cin >> m;
        while (m--) {
            cin >> s1 >> convertRate >> s2;
            id1 = mapIds[s1];
            id2 = mapIds[s2];
            dist[id1][id2] = convertRate;
        }

        bool isArbitrage = floydWarshall(dist, n); // O(N^3), N <= 30 -> This is complexity of this solution
        cout << "Case " << ++T << ": " << (isArbitrage ? "Yes" : "No") << endl;
    }

    return 0;
}