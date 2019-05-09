// Problem: 10227 Forests
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1168
// Author: Mai Thanh Hiep
// Complexity: O(P*P*T*LogP), P < 100, T < 100

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 99
int parent[MAX];
int ranks[MAX]; // max degree of graph

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
}

int findSet(int u) {
    int oldU = u;
    while (u != parent[u])
        u = parent[u];

    parent[oldU] = u;
    return u;
}

// return: true if success, else return false
bool unionSet(int u, int v) {
    int up = findSet(u);
    int vp = findSet(v);

    if (up == vp)
        return false;

    if (ranks[up] > ranks[vp]) {
        parent[vp] = up;
    } else if (ranks[up] < ranks[vp]) {
        parent[up] = vp;
    } else {
        parent[vp] = up;
        ranks[up]++;
    }
    return true;
}

bool isTheSameOption(bool* arr1, bool* arr2, int n) {
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    return true;
}

int main() {
    int tc;
    scanf("%d ", &tc);

    int T, P, i, j, differentSet;
    char s[10];
    bool options[MAX][MAX];
    while (tc--) {
        scanf("%d %d ", &P, &T);

        memset(options, 0, sizeof(options));
        while (gets(s)) {
            if(strcmp(s, "") == 0)
				break;
			sscanf(s, "%d %d", &i, &j);
			--i, --j;
            options[i][j] = true;
        }

        makeSet(P);
        differentSet = P;

        for (int i = 0; i < P; i++) { // O(P*P*T*LogP), P < 100, T < 100 -> This is complexity of this solution
            for (int j = i + 1; j < P; j++) {
                if (isTheSameOption(options[i], options[j], T)) { // O(T)
                    // Merge people i and people j to the same set
                    if (unionSet(i, j)) { // O(LogP)
                        differentSet--;
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
