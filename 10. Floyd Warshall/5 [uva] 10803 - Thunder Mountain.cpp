// Problem: 10803 - Thunder Mountain
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1744
// Author: Mai Thanh Hiep
// Complexity: O(n^3), n <= 100
/* Summary of problem:
        Input: There are n (1 < n < 101) coordinates (x, y) on planes (0 <= x,y <= 1023), there exists a direct path between 2 point if distance <= 10,
            calculate the shortest path between every pair of 2 different points, find the path that have maximum distance.
        Output:
            If there exists no path between any 2 points
                -> print "Send Kurdy"
            else
                -> print maximum distance of the path have maximum distance

*/

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define INF INT_MAX

void floydWarshall(vector<vector<double>>& dist, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

double calcDistance(const pair<int, int>& p1, const pair<int, int>& p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

int main() {
    int N;
    cin >> N;

    int n;
    for (int tc = 1; tc <= N; tc++) {
        cin >> n;
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].first >> points[i].second;
        }

        vector<vector<double>> dist(n, vector<double>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double w = calcDistance(points[i], points[j]);
                if (w <= 10) {
                    dist[i][j] = dist[j][i] = w;
                } else {
                    dist[i][j] = INF;
                }
            }
        }

        floydWarshall(dist, n); // O(n^3), n <= 100 -> This is complexity of this algorithm

        double maxDist = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                maxDist = max(maxDist, dist[i][j]);
            }
        }

        cout << "Case #" << tc << ":" << endl;

        if (maxDist == INF)
            cout << "Send Kurdy" << endl;
        else
            printf("%0.4f\n", maxDist);
        cout << endl;
    }

	return 0;
}
