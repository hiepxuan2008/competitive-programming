// Problem: Problem Makes Problem
// Author: Mai Thanh Hiep
/* Idea:
		Return: C(n+k-1, k-1) 
				= (n+k-1)! / ((k-1)! * n!) 
				= (((n+k-1)! % MOD) * modInverse((k-1)! * n! % MOD, MOD) % MOD
				; n, k <= 10^6
*/
// Complexity: O(2*10^6) + T * O(30), T <= 25000

#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007
#define MAX 2*1000000

vector<int> extendedEuclid(int b, int m) {
	vector<int> result;
	int x1 = 0, y1 = 1;
	int x2 = 1, y2 = 0;
	int q, r;
	int x = 1, y = 0;
	while (m != 0) {
		q = b / m;
		r = b % m;
		x = x2 - q * x1;
		y = y2 - q * y1;
		x2 = x1, y2 = y1;
		x1 = x, y1 = y;
		b = m, m = r;
	}

	result.push_back(b);
	result.push_back(x2);
	result.push_back(y2);
	return result;
}

// O(Log(M))
int modInverse(int b, int m) {
	vector<int> result = extendedEuclid(b, m);
	int gcd = result[0];
	int x = result[1];
	int y = result[2];
	if (gcd != 1)
		return -1;

	return (x + m) % m;
}

int main() {
	int t, n, k;
	cin >> t;

	long long fact[MAX];
	fact[0] = 1;
	for (long long i = 1; i < MAX; i++) { // O(MAX), MAX = 2*10^6
		fact[i] = fact[i - 1] * i % MOD;
	}

	for (int tc = 1; tc <= t; tc++) { // T * O(Log(MOD)) = T * O(30), T <= 25000, MOD = 10^9
		cin >> n >> k;
		cout << "Case " << tc << ": ";
		cout << (fact[n + k - 1] * (long long)(modInverse(fact[k - 1] * fact[n] % MOD, MOD))) % MOD << endl;
	}

	return 0;
}