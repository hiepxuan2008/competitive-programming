// Problem: 10820 - Send a Table
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1761
// Author: Mai Thanh Hiep
// Complexity: O(MAX * sqrt(MAX)) + T * O(N), MAX = 50000

#include <iostream>
using namespace std;

// O(sqrt(N))
int phi(int n) {
	int result = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result = result / i * (i - 1);
		}
	}

	if (n > 1)
		result = result / n * (n - 1);

	return result;
}

#define MAX 50001
int main() {
	int n;
	int fPhi[MAX];

	for (int i = 1; i <= MAX; i++) // O(MAX * sqrt(MAX)), MAX = 50000
		fPhi[i] = phi(i); // O(sqrt(i))

	while (cin >> n) {
		if (n == 0)
			break;

		int sumPhi = 0;
		for (int i = 1; i <= n; i++) { // O(N)
			sumPhi += fPhi[i];
		}
		cout << (2 * sumPhi - 1) << endl;
	}

	return 0;
}