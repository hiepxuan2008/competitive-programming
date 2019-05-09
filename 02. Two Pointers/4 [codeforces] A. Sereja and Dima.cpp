// Problem: A. Sereja and Dima
// Link: https://codeforces.com/problemset/problem/381/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>

using namespace std;

#define MAX 1000
int cards[MAX];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cards[i];
    }

    int i = 0;
    int j = n - 1;
    int points[] = {0, 0};
    int turn = 0;
    int take = 0;
    while (i <= j) {
        if (cards[i] >= cards[j]) {
            take = cards[i];
            i++;
        } else {
            take = cards[j];
            j--;
        }

        points[turn] += take;
        turn = 1 - turn;
    }

    cout << points[0] << " " << points[1] << endl;

    return 0;
}
