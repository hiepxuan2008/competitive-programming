// Problem: 11995 - I Can Guess the Data Structure!
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3146
// Solution: Mai Thanh Hiep

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c, v;
    while (cin >> n) {
        stack<int> s;
        queue<int> q;
        priority_queue<int> maxHeap;
        bool isStack = true, isQueue = true, isMaxHeap = true;

        while (n--) {
            cin >> c >> v;

            switch (c) {
                case 1: {
                    if (isStack) s.push(v);
                    if (isQueue) q.push(v);
                    if (isMaxHeap) maxHeap.push(v);
                    break;
                }
                case 2: {
                    if (isStack) {
                        if (s.empty() || v != s.top())
                            isStack = false;
                        else
                            s.pop();
                    }

                    if (isQueue) {
                        if (q.empty() || v != q.front())
                            isQueue = false;
                        else
                            q.pop();
                    }

                    if (isMaxHeap) {
                        if (maxHeap.empty() || v != maxHeap.top())
                            isMaxHeap = false;
                        else
                            maxHeap.pop();
                    }
                    break;
                }
            }
        }

        if (isStack && !isQueue && !isMaxHeap) {
            cout << "stack" << endl;
        } else if (!isStack && isQueue && !isMaxHeap) {
            cout << "queue" << endl;
        } else if (!isStack && !isQueue && isMaxHeap) {
            cout << "priority queue" << endl;
        } else if (!isStack && !isQueue && !isMaxHeap) {
            cout << "impossible" << endl;
        } else {
            cout << "not sure" << endl;
        }
    }

    return 0;
}
