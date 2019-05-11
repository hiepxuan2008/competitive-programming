// Problem: Mattey Multiplication
// Link: https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/practice-problems/algorithm/mattey-multiplication-6/
// Author: Mai Thanh Hiep
// Complexity: T * O(LogM), M <= 10^16, T <= 5*10^4

#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;

	unsigned long long n, m;
	while (t--) {
		cin >> n >> m;

		bool firstItem = true;
		unsigned long long x;
		int shiftLeft;
		while (m != 0) { // Log(M)
			x = 1L;
			shiftLeft = 0;
			while ((x << 1) <= m) {
				shiftLeft++;
				x <<= 1;
			}

			if (firstItem) {
				firstItem = false;
				cout << "(" << n << "<<" << shiftLeft << ")";
			} else {
				cout << " + (" << n << "<<" << shiftLeft << ")";
			}

			m = m - x;
		}
		cout << endl;
	}

	return 0;
}