// Problem: 10245 - The Closest Pair Problem
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1186
// Author: ...
// Complexity: T * O(NLogN), N <= 10^4

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

Point splittedPoints[MAX];

double calcDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool xComparator(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

bool yComparator(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

double bruteForce(vector<Point>& points, int left, int right) {
    double minDist = INF;
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j < right; j++) {
            minDist = min(calcDistance(points[i], points[j]), minDist);
        }
    }
    return minDist;
}

double stripClosest(vector<Point>& points, int left, int right, int mid, double minDist) {
    Point midPoint = points[mid];
    int n = 0;
    for (int i = left; i < right; i++) {
        if (abs(points[i].x - midPoint.x) < minDist)
            splittedPoints[n++] = points[i];
    }
    sort(splittedPoints, splittedPoints + n, yComparator);
    double smallest = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (splittedPoints[j].y - splittedPoints[i].y) < minDist; j++) {
            double d = calcDistance(splittedPoints[i], splittedPoints[j]);
            smallest = min(smallest, d);
        }
    }
    return smallest;
}

double closestUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3)
        return bruteForce(points, left, right);

    int mid = (left + right) / 2;
    double leftDist = closestUtil(points, left, mid); // exclude mid
    double rightDist = closestUtil(points, mid + 1, right); // exclude mid
    double minDist = min(leftDist, rightDist);
    return min(minDist, stripClosest(points, left, right, mid, minDist));
}

int main() {
    int n;

    while (true) {
        cin >> n;
        if (n == 0)
            break;

        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }

        sort(points.begin(), points.end(), xComparator);
        double minDistance = closestUtil(points, 0, points.size());
        if (minDistance >= 10000) {
            cout << "INFINITY" << endl;
        } else {
            cout << fixed << setprecision(4) << minDistance << endl;
        }
    }

    return 0;
}