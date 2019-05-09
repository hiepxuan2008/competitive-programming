// Problem: 10246 - Asterix and Obelix
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1187
// Author: Mai Thanh Hiep
// Complexity: O(C^3), C <= 80

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;
#define INF INT_MAX

void floydWarshall(vector<vector<int>>& dist, int V, vector<int> fcost) {
    vector<vector<int>> maxCost(V, vector<int>(V));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            maxCost[i][j] = max(fcost[i], fcost[j]);
            if (dist[i][j] != INF)
                dist[i][j] = dist[i][j] + maxCost[i][j];
        }
    }

    for (int e = 0; e < 2; e++) {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j] - min(maxCost[i][k], maxCost[k][j])) {
                        dist[i][j] = dist[i][k] + dist[k][j] - min(maxCost[i][k], maxCost[k][j]);
                        maxCost[i][j] = max(maxCost[i][k], maxCost[k][j]);
                    }
                }
            }
        }
    }
}

int main() {
	int T = 0;
	int C, R, Q;
	int c1, c2, d;
	while (true) {
		cin >> C >> R >> Q;
		if (C + R + Q == 0)
			break;

		vector<vector<int>> dist(C, vector<int>(C));
		vector<int> fcost(C);
		for (int i = 0; i < C; i++) {
			for (int j = 0; j < C; j++) {
				if (i == j) {
					dist[i][j] = 0;
				} else {
					dist[i][j] = INF;
				}
			}
		}

		for (int i = 0; i < C; i++) {
			cin >> fcost[i];
		}

		while (R--) {
			cin >> c1 >> c2 >> d;
			--c1, --c2;
			dist[c1][c2] = dist[c2][c1] = d;
		}

		floydWarshall(dist, C, fcost); // O(C^3), C <= 80 -> This is complexity of this algorithm

		if (T > 0)
            cout << endl; // Print a blank line between two consecutive test cases

		cout << "Case #" << ++T << endl;
		while (Q--) {
			cin >> c1 >> c2;
			--c1, --c2;
			if (dist[c1][c2] == INF) {
				cout << -1 << endl;
			} else {
				cout << dist[c1][c2] << endl;
			}
		}
	}

	return 0;
}
