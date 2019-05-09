// Problem: 10226 - Hardwood Species
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1167
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

int main() {
	int t;
	scanf("%d\n\n", &t);

	string s;
	map<string, int> mymap;
	while (t--) {
		mymap.clear();
		int n = 0;
		while (getline(cin, s)) {
			if (s == "")
				break;

			n++;
			mymap[s]++;
		}

		for (map<string, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
			cout << it->first << " " << fixed << setprecision(4) << (it->second * 100.0f / n) << endl;
		}

		if (t > 0) {
            cout << endl;
		}
	}

	return 0;
}
