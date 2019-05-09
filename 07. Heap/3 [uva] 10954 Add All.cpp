// Problem: 10954 - Add All
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1895
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0)
            break;

        priority_queue<int, vector<int>, greater<int>> pq;
        int x;
        for (int i = 0; i < n; i++) {
            cin >> x;
            pq.push(x);
        }

        long long totalCost = 0;
        long long cost;
        while (pq.size() > 1) {
            cost = pq.top();
            pq.pop();
            cost += pq.top();
            pq.pop();

            totalCost += cost;
            pq.push(cost);
        }

        cout << totalCost << endl;
    }

    return 0;
}
