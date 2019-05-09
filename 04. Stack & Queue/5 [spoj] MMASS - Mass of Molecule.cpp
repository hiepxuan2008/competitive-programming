// Problem: MMASS - Mass of Molecule
// Link: https://www.spoj.com/problems/MMASS/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

#define OPEN_PARENTHESIS -1

int getMass(char atom) {
    switch (atom) {
        case 'C':
            return 12;
        case 'O':
            return 16;
    }
    return 1; // Default H
}

int main() {
    char s[101];
    scanf("%s", s);

    int n = strlen(s);
    int multi = 1;
    int top;
    int temp;
    stack<int> mystack;
    for (int i = 0; i < n; i++) {
        // Open Parenthesis
        if (s[i] == '(') {
            mystack.push(OPEN_PARENTHESIS);
        }
        // Close Parenthesis
        else if (s[i] == ')') {
            temp = 0;
            while (!mystack.empty() && mystack.top() != OPEN_PARENTHESIS) {
                temp += mystack.top();
                mystack.pop();
            }
            mystack.pop(); // pop (
            mystack.push(temp);
        }
        // Number of occurrences
        else if (s[i] >= '2' && s[i] <= '9') {
            multi = s[i] - '0';
            top = mystack.top();
            mystack.pop();
            mystack.push(multi * top);
        }
        // Atom
        else {
            mystack.push(getMass(s[i]));
        }
    }

    int ans = 0;
    while (!mystack.empty()) {
        ans += mystack.top();
        mystack.pop();
    }

    printf("%d\n", ans);

    return 0;
}
