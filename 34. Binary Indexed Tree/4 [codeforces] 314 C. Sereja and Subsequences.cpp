// Problem: 314 C. Sereja and Subsequences
// Link: https://codeforces.com/problemset/problem/314/C
// Author: Mai Thanh Hiep
// Complexity: O(N * logMAX_X), where N <= 10^5 is size of array, MAX_X = 10^6
/**
 * Idea:
 *      It is clear that we need to calculate the sum of the products of elements of all the different non-decreasing subsequences of given sequence.
 *      Let's go through the sequence from left to right and maintain the array q[i]: what means the sum of all relevant sub-sequences,
 *      such that their last element is equal to i.
 *      Clearly, if the next number is x, then you need to put q[x] = sum (q[1] + q[2] + ... + q[x]) * x + x.
 *      The answer to the problem is the sum of q[i].
 *      To find all the amounts you can use Fenwick tree.
 *  Reference: https://codeforces.com/blog/entry/7905
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MOD = 1e9 + 7;
const int MAX_X = 1e6;

class BIT { // 1-based indexing
    vector<ll> bit;
public:
    BIT(int size) {
        bit.resize(size + 1);
    }

    void update(int id, ll val) {
        for (; id < (int)bit.size(); id += id & -id) {
            bit[id] = (bit[id] + val) % MOD;
        }
    }

    ll getSum(int id) {
        ll res = 0;
        for (; id > 0; id -= id & -id) {
            res = (res + bit[id]) % MOD;
        }
        return res;
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector <int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    BIT bit(MAX_X);
    for (int x : arr) { // O(N * logMAX_X)
        int newValue = (1LL * bit.getSum(x) * x + x) % MOD;
        int currValue = (bit.getSum(x) - bit.getSum(x - 1) + MOD) % MOD;
        bit.update(x, (newValue - currValue + MOD) % MOD);
    }
    cout << bit.getSum(MAX_X) << endl;
    return 0;
}