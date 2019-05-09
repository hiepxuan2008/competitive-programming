// Problem: QHEAP1
// Link: https://www.hackerrank.com/challenges/qheap1/problem
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int q;
	cin >> q;
    priority_queue<int, vector<int>, greater<int>> pq;
    priority_queue<int, vector<int>, greater<int>> removePq;
    int c, v;
    for (int i = 0; i < q; i++) {
        cin >> c;

        switch (c) {
            case 1:
                cin >> v;
                pq.push(v);
                break;
            case 2:
                cin >> v;
                removePq.push(v); // later remove
                // check and remove elements from pq
                while (!removePq.empty() && removePq.top() == pq.top()) {
                    pq.pop();
                    removePq.pop();
                }
                break;
            case 3:
                cout << pq.top() << endl;
                break;
        }
    }

    return 0;
}
