// Problem: STPAR - Street Parade
// Link: https://www.spoj.com/problems/STPAR/
// Solution: Mai Thanh Hiep
// Complexity: O(N)

#include <iostream>
#include <stack>
using namespace std;

#define MAX 1000
int arr[MAX];

int main() {
    int n;
    while (true) {
        cin >> n;

        if (n == 0)
            break;

        stack<int> mystack;
        int order = 1;
        int x;
        for (int i = 0; i < n; i++) {
            cin >> x;

            if (x != order) {
                // Check to pop in-order waiting trucks in stack
                while (!mystack.empty() && mystack.top() == order) {
                    mystack.pop();
                    order++; // next order
                }

                mystack.push(x); // push this truck into waiting list
            } else {
                order++; // next order
            }
        }

        // Check to pop in-order waiting trucks in stack
        while (!mystack.empty() && mystack.top() == order) {
            mystack.pop();
            order++;
        }

        cout << (mystack.empty() ? "yes" : "no") << endl;
    }

    return 0;
}
