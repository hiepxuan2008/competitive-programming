// Problem: Reverse Prime
// Link: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2657
// Author: Mai Thanh Hiep
// Complexity: O(Q * logN * logN), where Q is number of queries, N is number of Reverse Prime 7-digits numbers

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e7 + 5;

int spf[MAXN]; // spf[x] is the smallest prime factor of number x, where x >= 2

class BIT { // One-based indexing
    vector<int> bit;
public:
    BIT(int n) {
        bit.resize(n + 1);
    }
    int get(int id) {
        int sum = 0;
        while (id > 0) {
            sum += bit[id];
            id -= id & (-id);
        }
        return sum;
    }
    void update(int id, int val) {
        while (id < bit.size()) {
            bit[id] += val;
            id += id & (-id);
        }
    }
};

// O(Nlog(logN)) ~ O(N)
void sieve(int n) {
    for (int i = 2; i <= n; ++i)
        spf[i] = i;

    for (int i = 2; i * i <= n; i++) {
        if (spf[i] != i) continue; // skip if `i` is not a prime number
        for (int j = i * i; j <= n; j += i) {
            if (spf[j] == j) { // marking spf[j] if it is not previously marked
                spf[j] = i;
            }
        }
    }
}

int reverse(int n) {
    int ans = 0;
    while (n > 0) {
        ans = ans * 10 + n % 10;
        n /= 10;
    }
    return ans;
}

int getFactors(int n) { // O(logN)
    int ans = 0;
    while (n > 1) {
        ++ans;
        n /= spf[n];
    }
    return ans;
}

void preProcess(vector<int>& primes, vector<int>& nFactors) {
    sieve(MAXN - 1);
    for (int i = 1e6; i < 1e7; ++i) { // 1.000.000 -> 9.999.999 (7-digits number)
        int reverseNum = reverse(i);
        if (reverseNum >= 1e6) continue; // reverse number must be less than 10^6
        if (spf[reverseNum] != reverseNum) continue; // reverse number must be a prime number
        int cntFactor = getFactors(i);
        if (cntFactor > 0) {
            primes.push_back(i);
            nFactors.push_back(cntFactor);
        }
    }
}

int query(BIT& sumBit, BIT& cntBit, int n, int id) {
    int left = 1, right = n;
    while (left <= right) { // logN * logN
        int mid = left + (right - left) / 2;
        int cnt = cntBit.get(mid); // logN
        if (cnt == id) {
            return sumBit.get(mid);
        }
        if (cnt > id) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> primes, nFactors;
    preProcess(primes, nFactors);

    int n = primes.size();
    BIT sumBit(n), cntBit(n);
    for (int i = 1; i <= n; ++i) {
        sumBit.update(i, nFactors[i - 1]);
        cntBit.update(i, 1);
    }

    char cmd;
    int x;
    while (cin >> cmd >> x) {
        if (cmd == 'q') {
            int id = x + 1;
            cout << query(sumBit, cntBit, n, id) << '\n'; // O(logN * logN)
        } else { // delete x
            int id = lower_bound(primes.begin(), primes.end(), x) - primes.begin() + 1; // 1-based indexing
            sumBit.update(id, -nFactors[id - 1]); // O(logN)
            cntBit.update(id, -1); // O(logN)
        }
    }
}