// Problem: 10223 - How many nodes ?
// Link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1164
// Author: Mai Thanh Hiep
// Complexity: O(T * 20), where T is number of testcases

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll cat[22], n;
    cat[0] = 1;
    for (int i = 0; i < 20; ++i) cat[i+1] = (cat[i] * (4*i + 2)) / (i+2);
    while (cin >> n) {
        int ans = -1;
        for (int i = 1; i < 20; ++i) {
            if (cat[i] == n) {
                ans = i;
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}