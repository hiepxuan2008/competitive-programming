// Problem: 10171 - Meeting Prof. Miguel...
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1112
// Author: Mai Thanh Hiep
// Complexity: O(MAX^3), MAX = 26 => O(26^3)

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

#define MAX 'Z'-'A'+1
#define INF INT_MAX
using namespace std;

bool floydWarshall(int (*dist)[MAX], int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // check negative cycle
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0)
            return true;
    }
    return false;
}

int main() {
	int n;
	char age, direction, city1, city2;
	int energy;
	char src, dst;
	int distY[MAX][MAX];
	int distM[MAX][MAX];
	while (true) {
		cin >> n;
		if (n == 0)
			break;

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (i == j) {
                    distM[i][j] = distY[i][j] = 0;
                } else {
                    distM[i][j] = distY[i][j] = INF;
                }
            }
        }

		while (n--) {
			cin >> age >> direction >> city1 >> city2 >> energy;
			city1 -= 'A', city2 -= 'A';

			if (age == 'Y') {
                distY[city1][city2] = min(distY[city1][city2], energy);

                if (direction == 'B') {
                    distY[city2][city1] = min(distY[city2][city1], energy);
                }
			} else {
                distM[city1][city2] = min(distM[city1][city2], energy);

                if (direction == 'B') {
                    distM[city2][city1] = min(distM[city2][city1], energy);
                }
			}
		}

		cin >> src >> dst;
		src -= 'A', dst -= 'A';

		floydWarshall(distY, MAX); // O(MAX^3) = O(26^3)
		floydWarshall(distM, MAX); // O(MAX^3) = O(26^3)

		int minDist = INF;
		for (int i = 0; i < MAX; i++) { // O(MAX)
			if (distY[src][i] != INF && distM[dst][i] != INF && minDist > distY[src][i] + distM[dst][i]) {
				minDist = distY[src][i] + distM[dst][i];
			}
		}

		if (minDist != INF) {
			cout << minDist;
			for (int i = 0; i < MAX; i++) {
				if (distY[src][i] != INF && distM[dst][i] != INF && minDist == distY[src][i] + distM[dst][i]) {
					cout << " " << char(i + 'A');
				}
			}
			cout << endl;
		} else {
			cout << "You will never meet." << endl;
		}
	}

	return 0;
}
