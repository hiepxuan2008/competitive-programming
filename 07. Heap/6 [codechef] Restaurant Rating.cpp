// Problem: Restaurant Rating
// Link: https://www.codechef.com/problems/RRATING
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<int, vector<int>, greater<int>> minHeap; // top value is current minimum one-third of array k elements
    priority_queue<int> maxHeap;

    int n, c, x;
    cin >> n;

    int k = 0;
    while (n--) {
        cin >> c;
        switch (c) {
            case 1: {
                cin >> x;
                k++;

                // don't greater than current minimum one-third -> push to max heap
                if (minHeap.empty() || x <= minHeap.top()) {
                    maxHeap.push(x);
                }
                // greater than current minimum one-third -> pop current minHeap to maxHeap, push x to minHeap
                else {
                    maxHeap.push(minHeap.top());
                    minHeap.pop();
                    minHeap.push(x);
                }

                // push one more element to minHeap as minimum one-third of array k elements
                if (k % 3 == 0) {
                    minHeap.push(maxHeap.top());
                    maxHeap.pop();
                }
                break;
            }
            case 2: {
                if (minHeap.empty()) {
                    cout << "No reviews yet" << endl;
                } else {
                    cout << minHeap.top() << endl;
                }
                break;
            }
        }
    }

    return 0;
}
