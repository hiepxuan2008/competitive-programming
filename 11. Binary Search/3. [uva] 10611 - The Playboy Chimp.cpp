// Problem: 10611 - The Playboy Chimp
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=316&page=show_problem&problem=1552
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 50000
int arr[MAX];

int highestShortThanX(int* arr, int n, int x) {
	int l, r, m;
	l = 0;
	r = n - 1;
	while (l <= r) {
		m = (l + r) / 2;
		if (arr[m] < x && (m == r || arr[m + 1] >= x)) {
			return m;
		}
		else if (arr[m] >= x) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return -1;
}

int shortestTallerThanX(int* arr, int n, int x) {
	int l, r, m;
	l = 0;
	r = n - 1;
	while (l <= r) {
		m = (l + r) / 2;
		if (arr[m] > x && (m == l || arr[m - 1] <= x)) {
			return m;
		}
		else if (arr[m] <= x) {
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}
	return -1;
}

void printResult(int* arr, int index) {
	if (index == -1) {
		cout << "X";
	} else {
        cout << arr[index];
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int q, x;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> x;
		printResult(arr, highestShortThanX(arr, n, x));
		cout << " ";
		printResult(arr, shortestTallerThanX(arr, n, x));
		cout << endl;
	}

	return 0;
}
