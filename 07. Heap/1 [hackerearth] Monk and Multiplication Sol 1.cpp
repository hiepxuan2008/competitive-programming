// Problem: Monk and Multiplication
// Link: https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/monk-and-multiplication/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    priority_queue<long long> pq;
    long long x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pq.push(x);

        if (pq.size() < 3)
            cout << "-1" << endl;
        else {
            long long largest = pq.top();
            pq.pop();
            long long secondLargest = pq.top();
            pq.pop();
            long long thirdLargest = pq.top();
            pq.pop();
            cout << largest * secondLargest * thirdLargest << endl;

            pq.push(largest);
            pq.push(secondLargest);
            pq.push(thirdLargest);
        }
    }

    return 0;
}
