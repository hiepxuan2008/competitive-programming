// Problem: 515B. Drazil and His Happy Friends
// Link: https://codeforces.com/problemset/problem/516/E
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, b, g, x;
    cin >> n >> m;
    vector<bool> boyHappy(n, false);
    vector<bool> girlHappy(m, false);

    cin >> b;
    for (int i = 0; i < b; i++) {
        cin >> x;
        boyHappy[x] = true;
    }
    cin >> g;
    for (int i = 0; i < g; i++) {
        cin >> x;
        girlHappy[x] = true;
    }

    for (int i = 0; i < 100000; i++) {
        if (boyHappy[i % n] || girlHappy[i % m]) {
            boyHappy[i % n] = true;
            girlHappy[i % m] = true;
        }
    }

    bool result = true;
    for (int i = 0; i < n; i++)
        result &= boyHappy[i];
    for (int i = 0; i < m; i++)
        result &= girlHappy[i];

    cout << (result ? "Yes" : "No") << endl;

    return 0;
}