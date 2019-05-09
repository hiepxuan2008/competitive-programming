// Problem: Monk and Multiplication
// Link: https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/monk-and-multiplication/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> minHeap;
    long long x;
    long long res;
    for (int i = 0; i < n; i++) {
        cin >> x;

        if (minHeap.size() < 2) {
            minHeap.push_back(x);
            cout << "-1" << endl;
        } else if (minHeap.size() == 2) {
            minHeap.push_back(x);
            make_heap(minHeap.begin(), minHeap.end(), greater<long long>());

            res = 1;
            for (int i = 0; i < minHeap.size(); i++) {
                res *= minHeap[i];
            }
            cout << res << endl;
        } else {
            if (x > minHeap[0]) {
                minHeap[0] = x;
                make_heap(minHeap.begin(), minHeap.end(), greater<long long>());
            }

            res = 1;
            for (int i = 0; i < minHeap.size(); i++) {
                res *= minHeap[i];
            }
            cout << res << endl;
        }
    }

    return 0;
}
