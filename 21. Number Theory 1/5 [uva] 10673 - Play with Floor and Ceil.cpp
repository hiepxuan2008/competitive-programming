// Problem: 10673 - Play with Floor and Ceil
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1614
// Solution: Mai Thanh Hiep
// Complexity: T * O(Log(N)), N <= 10^8, T <= 1000
// Idea
/*
    Case 1: x % k > 0
        a = x/k
        b = x/k+1
        Cause a, b are consecutive numbers, GCD(a, b) will be 1
        Find p, q that : a*p + b*q = x
        Step 1 : Find p1, q1 that:		a*p1 + b*q1 = 1 using extendedEuclid
        Step 2: Multy equality by x:	a*p1*x + b*q1*x = x
        => The result will be: p = p1*x, q = q1*x
    Case 2: x % k == 0
            (x/k)(p + q) = x
        =>	p + q = k
        => The result: p = 0, q = k
*/

#include <iostream>
#include <vector>
using namespace std;

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

long long multy(long long x, long long y) {
    return x * y;
}

int main() {
    int t, x, k;
    int a, b;
    cin >> t;

    while (t--) {
        cin >> x >> k;

        if (x % k > 0) {
            a = x / k; // Floor Interger
            b = a + 1; // Ceil Interger
            vector<int> result = extendedEuclid(a, b); // O(Log(min(a, b))); a, b <= 10^8 => O(Log(N)), N <= 10^8 -> This is complexity of this solution
            cout << multy(result[1], x) << " " << multy(result[2], x) << endl;
        } else {
            cout << 0 << " " << k << endl;
        }
    }

    return 0;
}