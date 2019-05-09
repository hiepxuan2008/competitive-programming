// Problem: 10227 Forests
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1168
// Author: Mai Thanh Hiep
// Complexity: O(P*P*T), P < 100, T < 100

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAX 99

bool isTheSameOption(bool* arr1, bool* arr2, int n) {
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    return true;
}

int main() {
    int tc;
    scanf("%d ", &tc);

    int T, P, i, j;
    char s[10];
    bool options[MAX][MAX];
    bool visited[MAX];
    while (tc--) {
        scanf("%d %d ", &P, &T);

        memset(options, 0, sizeof(options));
        memset(visited, 0, sizeof(visited));

        while (gets(s)) {
            if(strcmp(s, "") == 0)
				break;
			sscanf(s, "%d %d", &i, &j);
			--i, --j;
            options[i][j] = true;
        }

        int differentSet = 0;
        for (int i = 0; i < P; i++) { // O(P*P*T), P < 100, T < 100 -> This is complexity of this solution
            if (!visited[i]) {
                visited[i] = true;
                differentSet++;

                for (int j = i + 1; j < P; j++) {
                    if (!visited[j] && isTheSameOption(options[i], options[j], T)) { // O(T)
                        visited[j] = true;
                    }
                }
            }
        }

        cout << differentSet << endl;

        if (tc > 0)
            cout << endl;
    }

    return 0;
}
