// Problem: 10158 - War
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099
// Author: Mai Thanh Hiep
// Complexity: NUMBER_OF_COMMAND * Log(2 * N), N <= 10000

#include <iostream>
#include <vector>
using namespace std;

#define MAXN 10000
#define MAX 2 * MAXN
int parent[MAX];
int ranks[MAX]; // max degree of graph
int n;

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

int getEnemyId(int x) {
    return x + n;
}

bool areFriends(int x, int y) {
    return findSet(x) == findSet(y) || findSet(getEnemyId(x)) == findSet(getEnemyId(y));
}

bool areEnemies(int x, int y) {
    return findSet(x) == findSet(getEnemyId(y)) || findSet(y) == findSet(getEnemyId(x));
}

// Return: true if success, else return false
bool setFriends(int x, int y) {
    if (areEnemies(x, y))
        return false;

    unionSet(x, y);
    unionSet(getEnemyId(x), getEnemyId(y));
    return true;
}

// Return: true if success, else return false
bool setEnemies(int x, int y) {
    if (areFriends(x, y))
        return false;

    unionSet(x, getEnemyId(y));
    unionSet(y, getEnemyId(x));
    return true;
}

int main() {
    cin >> n;

    makeSet(n * 2);

    int c, x, y;
    while (true) {
        cin >> c >> x >> y;
        if (c == 0)
            break;

        switch (c) {
            case 1:
                if (!setFriends(x, y))
                    cout << -1 << endl;
                break;
            case 2:
                if (!setEnemies(x, y))
                    cout << -1 << endl;
                break;
            case 3:
                cout << (areFriends(x, y) ? 1 : 0) << endl;
                break;
            case 4:
                cout << (areEnemies(x, y) ? 1 : 0) << endl;
                break;
        }
    }

    return 0;
}
