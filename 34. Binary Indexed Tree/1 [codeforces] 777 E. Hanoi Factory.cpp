// Problem: 777 E. Hanoi Factory
// Link: https://codeforces.com/problemset/problem/777/E
// Author: Mai Thanh Hiep
// Complexity: O(N * logN), where N <= 10^5 is size of array
/**
 * Idea:
 *  1. Sort rings in decreasing order of outer radius, if the same outer radius then sort by decreasing of inner radius.
 *      - Sort rings in decreasing order of outer radius: Because ring[i] can put on top ring[j] (j < i) only if ring[i].outer <= ring[j].outer.
 *      - If the same outer radius then sort by decreasing of inner radius: Because rings with the same outer radius can always
 *          put on top of others, so we want the top as minimum inner radius as possible. (to minimize chance new ring to fall inside them).
 *  2. Iterating rings in that order, ring[i].outer is always <= ring[j].outer (j < i). So we don't need to care about outer radius anymore.
 *     - For current ring[i], we need to find the largest height tower so far which top is ring[j] and ring[i] can put on the top of ring[j].
 *     - To put on top of ring[j], ring[i] should not fall into ring[j], so ring[i].outer must be greater than ring[j].inner.
 *     - Let F[x] is the largest height tower so far which inner radius <= x. This is max elements in [1..x] if we build the Binary Indexed Tree.
 *     For (Ring& r : arr)
 *          ll maxHeight = bit.getMax(r.outer - 1); // Get the largest height tower where ring[j] is on the top, and ring[j].inner < ring[i].outer
 *          ll currHeight = maxHeight + r.height;
 *          bit.update(r.inner, currHeight)
 *  3. Since outer radius, inner radius is too big <= 10^9, we can't store in our Fenwick Tree. But we know that there is maximum 2*10^5 different values.
 *      So we can compress their radius to 2*10^5 as long as we keep the relative comparison between inner, outer radius.
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class BIT { // 1-based indexing
    vector<ll> bit;
public:
    BIT(int size) {
        bit.resize(size + 1);
    }
    void update(int id, ll val) {
        for (; id < (int)bit.size(); id += id & -id) {
            bit[id] = max(bit[id], val);
        }
    }
    ll getMax(int id) {
        ll res = 0;
        for (; id > 0; id -= id & -id) {
            res = max(res, bit[id]);
        }
        return res;
    }
};

struct Ring {
    int outer, inner, height;
    Ring(int outer = 0, int inner = 0, int radius = 0) : outer(outer), inner(inner), height(radius) {}

    bool operator < (const Ring& other) const {
        if (outer != other.outer) return outer < other.outer;
        return inner < other.inner;
    }
};

int compress(vector<Ring>& arr) {
    vector<int> uniqueSorted;
    for (Ring& r : arr) {
        uniqueSorted.push_back(r.inner);
        uniqueSorted.push_back(r.outer);
    }
    // Remove duplicated values, make the list sorted
    sort(uniqueSorted.begin(), uniqueSorted.end()); // O(N*logN)
    uniqueSorted.erase(unique(uniqueSorted.begin(), uniqueSorted.end()), uniqueSorted.end());

    for (Ring& r : arr) { // O(N*logN)
        r.inner = lower_bound(uniqueSorted.begin(), uniqueSorted.end(), r.inner) - uniqueSorted.begin() + 1;
        r.outer = lower_bound(uniqueSorted.begin(), uniqueSorted.end(), r.outer) - uniqueSorted.begin() + 1;
    }
    return uniqueSorted.size();
}
int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Ring> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].inner >> arr[i].outer >> arr[i].height;
    }
    sort(arr.rbegin(), arr.rend()); // O(N*logN)

    int nUnique = compress(arr); // O(N*logN)
    BIT bit(nUnique);
    ll ans = 0;
    for (Ring& r : arr) { // O(N*logN)
        ll maxHeight = bit.getMax(r.outer - 1); // Get the largest height tower where ring[j] is on the top, and ring[j].inner < ring[i].outer
        ll currHeight = maxHeight + r.height;
        bit.update(r.inner, currHeight);
        ans = max(ans, currHeight);
    }
    cout << ans << '\n';
    return 0;
}