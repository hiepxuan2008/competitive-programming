// Problem: ONP - Transform the Expression
// Link: https://www.spoj.com/problems/ONP/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

#define MAX 401

int main() {
	int t;
	scanf("%d", &t);
	char express[MAX];
	char result[MAX];

	while (t--) {
        scanf("%s", express);

        stack<char> mystack;
        int n = 0;
        int len = strlen(express);
        for (int i = 0; i < len; i++) {
            char c = express[i];
            if (c >= 'a' && c <= 'z') {
                result[n++] = c;
            } else if (c == ')') {
                while (!mystack.empty() && mystack.top() != '(') {
                    result[n++] = mystack.top();
                    mystack.pop();
                }

                if (!mystack.empty()) {
                    mystack.pop(); // pop (
                }
            } else {
                mystack.push(c);
            }
        }
        result[n] = '\0'; // end character of string

        // Print the result
        printf("%s\n", result);
	}

	return 0;
}
