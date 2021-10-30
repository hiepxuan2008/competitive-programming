// Problem: 678 C. Joty and Chocolate
// Link: https://codeforces.com/problemset/problem/678/C
// Author: Mai Thanh Hiep
// Complexity: O(1)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

ll cntDividend(ll n, ll x) {
    return n/x;
}

ll lcm(ll a, ll b) {
    return 1LL * a * b / __gcd(a, b);
}

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;

    ll ans = cntDividend(n, a) * p + cntDividend(n, b) * p - cntDividend(n, lcm(n, b)) * min(p, q);
    cout << ans << endl;

    return 0;
}