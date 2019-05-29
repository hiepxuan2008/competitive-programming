// Problem: 1009. K-based Numbers
// Link: http://acm.timus.ru/problem.aspx?num=1009
// Author: Mai Thanh Hiep
// Complexity: O(N), N <= 16

#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;

struct Digit {
	ll zeros;
	ll nonZeros;
};

int main() {
	int n, k;
	cin >> n >> k;

	vector<Digit> count(n);
	count[0].zeros = 0; // The number can't be leading with 0
	count[0].nonZeros = k - 1; // [1, k - 1]

	for (int i = 1; i < n; i++) {
		count[i].zeros = count[i - 1].nonZeros; // can't contain two successive zeros
		count[i].nonZeros = (count[i - 1].nonZeros + count[i - 1].zeros) * (k - 1);
	}

	cout << (count[n - 1].zeros + count[n - 1].nonZeros) << endl;

	return 0;
}