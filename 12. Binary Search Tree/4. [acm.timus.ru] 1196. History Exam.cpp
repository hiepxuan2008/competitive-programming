// Problem: 1196. History Exam
// Link: http://acm.timus.ru/problem.aspx?space=1&num=1196
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
	int n, x;
	cin >> n;

	unordered_set<int> myset;
	for (int i = 0; i < n; i++) {
        cin >> x;
        myset.insert(x);
	}

	int m;
	cin >> m;
	int cntExist = 0;
	for (int i = 0; i < m; i++) {
        cin >> x;
        if (myset.find(x) != myset.end()) {
            cntExist++;
        }
	}

	cout << cntExist << endl;

	return 0;
}
