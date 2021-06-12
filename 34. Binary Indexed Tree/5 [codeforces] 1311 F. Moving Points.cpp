// Problem: 1311 F. Moving Points
// Link: https://codeforces.com/problemset/problem/1311/F
// Author: Mai Thanh Hiep
// Complexity: O(N * logN), where N <= 2*10^5 is number of points.
/*
 * Idea:
 *      - Two points i and j concise if and only if xi < xj and vi > vj. So in that case, the minimum distance will be 0.
 *      - Now we only care to calculate minimum sum distance of pairs of points i and j, only when xi < xj and vi <= vj.
 *          Since when t increasing, the distance always increasing. So the minimum distance will be xj - xi.
 *      - We sort `points` by increasing order of their `xj`.
 *      - Then we iterate point (xj, vj) in our `points`, and calculate sum of minimum distance between current point j and previous points.
 *      - For (xj, vj) in points:
 *          + We need to calculate sum of minimum distance between points i and current point j, only when vi <= vj
 *          + We can use 1 Fenwick Tree named `cntBit` to store count of points i, where vi <= vj
 *          + We can use 1 Fenwick Tree named `coordBit` store sum of points j coordinate, where vi <= vj
 *          + Binary search on unique sorted speeds, to find a `pos` in Fenwick Tree, where vi <= vj
 *          + Then: ans += xj * cntBit.getSum(pos) - coordBit.getSum(pos)
 *          + Update: cntBit.update(pos, 1); coordBit.update(pos, xj)
 *
*       Idea Referenced from: https://codeforces.com/blog/entry/74224
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class BIT { // One-based indexing
private:
    vector<ll> bit;
public:
    BIT(int n) {
        bit.resize(n + 1);
    }
    ll getSum(int id) {
        ll sum = 0;
        while (id > 0) {
            sum += bit[id];
            id -= id & (-id);
        }
        return sum;
    }
    void update(int id, int val) {
        while (id < (int) bit.size()) {
            bit[id] += val;
            id += id & (-id);
        }
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) cin >> points[i].first;
    for (int i = 0; i < n; ++i) cin >> points[i].second;
    sort(points.begin(), points.end()); // sort by increasing order of coordinate

    vector<int> uniqueSortedSpeeds;
    for (auto &p : points) uniqueSortedSpeeds.push_back(p.second);
    sort(uniqueSortedSpeeds.begin(), uniqueSortedSpeeds.end()); // O(N*logN)
    uniqueSortedSpeeds.resize(unique(uniqueSortedSpeeds.begin(), uniqueSortedSpeeds.end()) - uniqueSortedSpeeds.begin());

    ll ans = 0;
    int size = uniqueSortedSpeeds.size();
    BIT cntBit(size), coordBit(size);
    for (auto [x, v] : points) { // O(N*logN)
        int pos = lower_bound(uniqueSortedSpeeds.begin(), uniqueSortedSpeeds.end(), v) - uniqueSortedSpeeds.begin() + 1; // 1-based indexing
        ans += cntBit.getSum(pos) * x - coordBit.getSum(pos);
        cntBit.update(pos, 1);
        coordBit.update(pos, x);
    }
    cout << ans << endl;

    return 0;
}