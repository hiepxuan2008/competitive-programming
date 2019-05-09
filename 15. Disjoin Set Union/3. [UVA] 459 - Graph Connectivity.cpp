// Problem: 459 - Graph Connectivity
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=400
// Author: Mai Thanh Hiep
// Complexity: O(M * LogN), M <= 26^2, N <= 26

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 'Z'-'A'+1
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

int main() {
    int tc;
    scanf("%d\n\n", &tc);

    int N, M, i, j;
    string s;
    int differentSet;
    while (tc--) {
        getline(cin, s);
        N = s[0] - 'A' + 1; // This character represents the largest node name in the graph

        differentSet = N;
        makeSet(N);

        M = 0;
        while (true) { // O(M * LogN), M <= 26^2, N <= 26 -> This is complexity of this solution
            if (!getline(cin,s) || s.empty())
                break;

            i = s[0] - 'A';
            j = s[1] - 'A';

            if (unionSet(i, j)) { // Log(N)
                differentSet--;
            }
            M++;
        }

        cout << differentSet << endl;
        if (tc > 0)
            cout << endl;
    }

    return 0;
}
