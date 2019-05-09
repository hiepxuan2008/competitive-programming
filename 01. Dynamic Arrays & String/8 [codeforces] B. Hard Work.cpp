// Problem: B. Hard Work
// Link: http://codeforces.com/problemset/problem/61/B
// Solution: Mai Thanh Hiep
// Complexity: 3! * 600 * n (n <= 1000)

#include <iostream>
#include <string.h>
using namespace std;

bool isSignChar(char c) {
    return c == '-' || c == ';' || c == '_';
}

void normalize(string& input) {
    int n = input.size();

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (!isSignChar(input[i])) {
            input[j++] = tolower(input[i]);
        }
    }
    input.resize(j); // update new size
}

int main() {
    string initStrList[3];
    for (int i = 0; i < 3; i++) {
        cin >> initStrList[i];
    }

    // Remove sign chars and convert to lowercase letters
    for (int i = 0; i < 3; i++) {
        normalize(initStrList[i]);
    }

    // Concatenate initialize string together
    string testList[6];
    int nTest = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i != j && j != k && i != k) {
                    testList[nTest++] = initStrList[i] + initStrList[j] + initStrList[k];
                }
            }
        }
    }

    int n;
    string str;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> str;
        normalize(str);

        bool isCorrect = false;
        for (int j = 0; j < 6; j++) {
            if (str == testList[j]) {
                isCorrect = true;
                break;
            }
        }

        cout << (isCorrect ? "ACC" : "WA") << endl;
    }

    return 0;
}
