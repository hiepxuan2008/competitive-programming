// Problem: A. Ice Skating
// Link: https://codeforces.com/problemset/problem/217/A
// Author: Mai Thanh Hiep
// Complexity: N*N*LogN, N <= 100

#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
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
    int n;
    cin >> n;

    makeSet(n);
    vector<pair<int, int>> snowDrift(n);
    for (int i = 0; i < n; i++) {
        cin >> snowDrift[i].first >> snowDrift[i].second;
    }

    int differentSet = n;
    for (int i = 0; i < n; i++) { // N*N*LogN, N <= 100 -> This is complexity of this problem
        for (int j = i + 1; j < n; j++) {
            if (snowDrift[i].first == snowDrift[j].first || snowDrift[i].second == snowDrift[j].second) {
                if (unionSet(i, j)) { // O(LogN)
                    differentSet--;
                }
            }
        }
    }

    cout << differentSet - 1 << endl;

    return 0;
}
