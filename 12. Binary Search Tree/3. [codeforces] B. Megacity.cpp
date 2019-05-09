// Problem: B. Megacity
// Link: https://codeforces.com/problemset/problem/424/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <iomanip>
using namespace std;

#define MEDACITY_PEOPLE_REQUIRE 1000000

int main() {
	int n, s;
	cin >> n >> s;

	map<int, int> mapRadiusToPeople;
	int x, y, k;
	for (int i = 0; i < n; i++) {
        cin >> x >> y >> k;
        mapRadiusToPeople[x*x + y*y] += k;
	}

	int population = s;
	int minRadius = -1;
	for (map<int, int>::iterator it = mapRadiusToPeople.begin(); it != mapRadiusToPeople.end(); ++it) {
        population += it->second;
        if (population >= MEDACITY_PEOPLE_REQUIRE) { // can become megacity
            minRadius = it->first;
            break;
        }
	}

	if (minRadius == -1)
        cout << -1 << endl;
    else
        cout << fixed << setprecision(6) << sqrt(minRadius) << endl;

	return 0;
}
