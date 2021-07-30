// Topic: Chinese Remainder Theorem
// Source: BigO Coding Center

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int extend_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extend_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

int modInverse(int b, int m) {
    int g, x, y;
    g = extend_gcd(b, m, x, y);
    if (g != 1) return -1;
    return x;
}

ll chineseRemainder(const vector<int>& a, const vector<int>& m, int mod) {
    ll res = 0;
    for (int i = 0; i < a.size(); ++i) {
        int M_i = mod / m[i];
        int y_i = modInverse(M_i, m[i]);
        res = (res + 1LL * a[i] * M_i * y_i) % mod;
    }
    return res;
}

int main() {
    vector<int> a({ 2, 3, 2 });
    vector<int> m({ 3, 5, 7 });

    cout << "Find x so that:\n";
    for (int i = 0; i < a.size(); ++i) {
        printf("x %% %d = %d\n", m[i], a[i]);
    }

    int mod = 1;
    for (int i : m) mod *= i;
    printf("x = %lld + %dk\n", chineseRemainder(a, m, mod), mod);

    return 0;
}