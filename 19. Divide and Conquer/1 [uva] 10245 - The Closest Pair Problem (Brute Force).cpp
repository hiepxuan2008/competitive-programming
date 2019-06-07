// Problem: 10245 - The Closest Pair Problem
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1186
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2), N <= 10000

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>      // std::setprecision

using namespace std;

#define MAX 10001
#define INF 1e9 // > sqrt(2) * 40.000 * 10.000

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {};
};

double calcDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    int n;
    Point points[MAX];

    while (true) {
        cin >> n;
        if (n == 0)
            break;

        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }

        double minDistance = INF;
        double dist;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                dist = calcDistance(points[i], points[j]);
                minDistance = min(dist, minDistance);
            }
        }

        if (minDistance >= 10000) {
            cout << "INFINITY" << endl;
        } else {
            cout << fixed << setprecision(4) << minDistance << endl;
        }
    }

    return 0;
}