// Problem: B. Eight Point Sets
// Link: https://codeforces.com/contest/334/problem/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
#define N 8

bool isExisted(const vector<int>& arr, int value) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == value)
            return true;

    return false;
}

void getUniqueNumbers(int arr[], int n, vector<int>& output) {
	for (int i = 0; i < n; ++i) {
		if (!isExisted(output, arr[i]))
			output.push_back(arr[i]);
	}
}

bool isArrayAllTrue(bool arr[], int n) {
    for (int i = 0; i < n; i++)
        if (!arr[i])
            return false;

    return true;
}

int main() {
	int xPoints[N];
	int yPoints[N];

	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &xPoints[i], &yPoints[i]);
	}

	vector<int> x;
	getUniqueNumbers(xPoints, N, x);
	vector<int> y;
	getUniqueNumbers(yPoints, N, y);

	if (x.size() != 3 || y.size() != 3) {
		printf("ugly");
		return 0;
	}

	// Sort x, y arrays, so that x1 < x2 < x3 and y1 < y2 < y3
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	// Check if points[i] is contained in set points (xi, yi) (1 <= i,j <= 3)
	bool check[N];
	memset(check, 0, N); //Init false values

	for (int xIndex = 0; xIndex < 3; ++xIndex)
        for (int yIndex = 0; yIndex < 3; ++yIndex)
            for (int k = 0; k < 8; ++k)
                if ((xIndex != 1 || yIndex != 1) //Except for point(x2, y2)
                    && xPoints[k] == x[xIndex] && yPoints[k] == y[yIndex]) {
                    check[k] = true;
                    break;
                }

    printf(isArrayAllTrue(check, N) ? "respectable" : "ugly");

	return 0;
}
