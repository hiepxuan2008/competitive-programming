// Problem: 10127 - Ones
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1068
// Author: Mai Thanh Hiep

#include <iostream>
using namespace std;

int main() {
	int n;
	while (cin >> n) {
		int x, y = 1;
		for (x = 1; ; x++) {
			if (y % n == 0)
				break;
			y = y * 10 + 1;
			y %= n;
		}
		cout << x << endl;
	}
	return 0;
}