// Problem: 429 D. Tricky Function
// Link: https://codeforces.com/problemset/problem/429/D
// Author: Mai Thanh Hiep
// Complexity: O(NLogN), N <= 10^5

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>
using namespace std;

#define MAX 100000
#define INF LLONG_MAX

struct Point {
	long long x, y;
	Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

Point splittedPoints[MAX];

long long power2(long long x) {
	return x * x;
}

long long f(const Point& p1, const Point& p2) {
	return power2(p1.x - p2.x) + power2(p1.y - p2.y);
}

bool xComparator(const Point& p1, const Point& p2) {
	return p1.x < p2.x;
}

bool yComparator(const Point& p1, const Point& p2) {
	return p1.y < p2.y;
}

long long bruteForce(vector<Point>& points, int left, int right) {
	long long minDist = INF;
	for (int i = left; i < right; i++) {
		for (int j = i + 1; j < right; j++) {
			minDist = min(f(points[i], points[j]), minDist);
		}
	}
	return minDist;
}

long long combine(vector<Point>& points, int left, int right, int mid, long long minDist) {
	Point midPoint = points[mid];
	int n = 0;
	for (int i = left; i < right; i++) {
		if (power2(points[i].x - midPoint.x) < minDist)
			splittedPoints[n++] = points[i];
	}
	sort(splittedPoints, splittedPoints + n, yComparator);
	long long smallest = INF;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n && power2(splittedPoints[j].y - splittedPoints[i].y) < minDist; j++) {
			long long d = f(splittedPoints[i], splittedPoints[j]);
			smallest = min(smallest, d);
		}
	}
	return smallest;
}

long long solve(vector<Point>& points, int left, int right) {
	if (right - left <= 3)
		return bruteForce(points, left, right);

	int mid = (left + right) / 2;
	long long leftDist = solve(points, left, mid); // exclude mid
	long long rightDist = solve(points, mid + 1, right); // exclude mid
	long long minDist = min(leftDist, rightDist);
	return min(minDist, combine(points, left, right, mid, minDist));
}

int main() {
	int n;
	scanf("%d", &n);

	vector<Point> points(n);
	vector<int> arr(n);
	vector<int> prefixSum(n);

	scanf("%d", &arr[0]);
	prefixSum[0] = arr[0];
	points[0] = Point(0, prefixSum[0]);

	for (int i = 1; i < n; i++) {
		scanf("%d", &arr[i]);
		prefixSum[i] = prefixSum[i - 1] + arr[i];
		points[i] = Point(i, prefixSum[i]);
	}

	sort(points.begin(), points.end(), xComparator);

	long long minDistance = solve(points, 0, points.size());
	cout << minDistance << endl;

	return 0;
}