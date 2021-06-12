// Problem: 100488 L. Two Heads Are Better
// Link: http://codeforces.com/problemset/gymProblem/100488/L
// Author: Mai Thanh Hiep
// Complexity: O(N + M), where N <= 10^5 is length of string, M <= 3*10^5 is the number of queries.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

class DequeReversible {
private:
    deque<char> dq;
    bool isReverse = false;

public:
    DequeReversible(const string& str, int left, int right) { // left, right inclusive
        for (int i = left; i <= right; ++i)
            dq.push_back(str[i]);
    }

    char popFront() {
        if (!isReverse) {
            char c = dq.front();
            dq.pop_front();
            return c;
        }
        char c = dq.back();
        dq.pop_back();
        return c;
    }

    char popBack() {
        if (isReverse) {
            char c = dq.front();
            dq.pop_front();
            return c;
        }
        char c = dq.back();
        dq.pop_back();
        return c;
    }

    void pushFront(char c) {
        if (!isReverse) {
            dq.push_front(c);
        } else {
            dq.push_back(c);
        }
    }

    void pushBack(char c) {
        if (isReverse) {
            dq.push_front(c);
        } else {
            dq.push_back(c);
        }
    }

    void reverse() {
        isReverse = !isReverse;
    }

    char front() {
        if (!isReverse)
            return dq.front();
        return dq.back();
    }

    char back() {
        if (isReverse)
            return dq.front();
        return dq.back();
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int n, l, r, m;
    cin >> n >> l >> r;
    string str;
    cin >> str;
    str = " " + str; // one-based indexing
    cin >> m;

    char cmd, x, y;
    DequeReversible left(str, 1, l-1);
    DequeReversible mid(str, l, r);
    DequeReversible right(str, r+1, n);

    while (m-- > 0) {
        cin >> cmd;
        if (cmd == 'S') {
            cin >> x >> y;
            if (x == 'L') {
                if (y == 'L') // move L pointer to the left side
                    mid.pushFront(left.popBack());
                else // move L pointer to the right side
                    left.pushBack(mid.popFront());
            } else { // x == 'R'
                if (y == 'L') // move R pointer to the left side
                    right.pushFront(mid.popBack());
                else // move R pointer to the right side
                    mid.pushBack(right.popFront());
            }
        } else if (cmd == 'R') { // reverse
            mid.reverse();
        } else if (cmd == 'Q') { // query
            cin >> x;
            if (x == 'L')
                cout << mid.front();
            else
                cout << mid.back();
        }
    }
    return 0;
}