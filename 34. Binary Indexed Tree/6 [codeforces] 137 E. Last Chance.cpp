// Problem: 137 E. Last Chance
// Link: https://codeforces.com/problemset/problem/137/E
// Author: Mai Thanh Hiep
// Complexity: O(N * logN), where N <= 2 * 10^5 is length of string.

#include <vector>
#include <iostream>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)
const int INF = 1e9;

class BIT { // one-based indexing
    vector<int> bit;
public:
    BIT(int size) {
        bit.assign(size + 1, INF);
    }

    void update(int id, int val) {
        for (; id < bit.size(); id += id & -id) {
            bit[id] = min(bit[id], val);
        }
    }

    int getMin(int id) {
        int res = INF;
        for (; id > 0; id -= id & -id) {
            res = min(res, bit[id]);
        }
        return res;
    }
};

// v <= 2c -> 2c - v >= 0, let score = 2c - v
int score(char c) {
    if (c < 'a') c += 32; // convert Uppercase to Lowercase character
    string vowels = "ueoai";
    if (vowels.find(c) != string::npos) return -1;
    return 2;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    int preSumScore = n+1; // Score formula : 2c-v, so values is in range [-n, 2n] -> increase by base (n+1) -> [1, 3n+1]
    BIT bit(3*n+1);
    int maxLength = 0, cnt = 0;
    bit.update(preSumScore, -1);
    for (int i = 0; i < n; ++i) { // O(NlogN)
        preSumScore += score(s[i]);
        int leftMost = bit.getMin(preSumScore); // O(logN)
        if (leftMost != INF) {
            if (maxLength < i - leftMost) {
                maxLength = i - leftMost;
                cnt = 1;
            } else if (maxLength == i - leftMost) {
                cnt += 1;
            }
        }
        bit.update(preSumScore, i); // O(logN)
    }
    if (maxLength == 0) {
        cout << "No solution" << endl;
    } else {
        cout << maxLength << " " << cnt << endl;
    }
    return 0;
}