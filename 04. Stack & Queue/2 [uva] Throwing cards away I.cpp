// Problem: 10935 - Throwing cards away I
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1876
// Solution: Mai Thanh Hiep
// Complexity: O(N)

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX 50
int arr[MAX];

void printNumbersSeparateByComma(const vector<int>& input) {
    if (input.size() > 0) {
        for (int i = 0; i < input.size() - 1; i++)
            cout << " " << input[i] << ",";

        cout << " " << input[input.size() - 1];
    }
}

int main() {
    int n;
    while (true) {
        cin >> n;

        if (n == 0)
            break;

        queue<int> myqueue;
        for (int i = 0; i < n; i++)
            myqueue.push(i + 1);

        vector<int> discardedCards;
        int top;
        while (myqueue.size() > 1) {
            // Throw top card
            top = myqueue.front();
            discardedCards.push_back(top);
            myqueue.pop();

            // Move next top card to bottom
            top = myqueue.front();
            myqueue.pop();
            myqueue.push(top);
        }

        cout << "Discarded cards:";
        printNumbersSeparateByComma(discardedCards);
        cout << endl;

        cout << "Remaining card:";
        if (myqueue.size() == 1) {
            cout << " " << myqueue.front();
        }
        cout << endl;
    }

    return 0;
}
