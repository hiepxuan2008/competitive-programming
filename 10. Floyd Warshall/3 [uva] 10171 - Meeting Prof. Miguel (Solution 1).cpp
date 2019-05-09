// Problem: 10171 - Meeting Prof. Miguel...
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1112
// Author: Mai Thanh Hiep
// Complexity: O(NLog(MAX) + MAX), MAX = 26 => O(NLog26)

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

#define MAX 'Z'-'A'+1
#define INF INT_MAX
using namespace std;

struct Target {
	int energy;
	int target;
	bool isYoung;

	Target(int _energy, int _target, bool _isYoung) : energy(_energy), target(_target), isYoung(_isYoung) {}
	Target(int _energy, int _target) : energy(_energy), target(_target), isYoung(false) {}
};

struct minHeapOption {
	bool operator()(const Target& a, const Target& b) {
		return a.energy > b.energy;
	}
};

// O(ELogV)
void dijikstra(int s, vector<vector<Target>>& graph, vector<int>& dist, bool isYoung) {
	priority_queue<Target, vector<Target>, minHeapOption> pq;
	dist[s] = 0;
	pq.push(Target(dist[s], s));

	while (!pq.empty()) {
        Target top = pq.top();
		pq.pop();
		int u = top.target;
		int w = top.energy;

		for (int i = 0; i < graph[u].size(); i++) {
			Target& neighbor = graph[u][i];
			int v = neighbor.target;

			if (neighbor.isYoung == isYoung && w + neighbor.energy < dist[v]) {
				dist[v] = w + neighbor.energy;
				pq.push(Target(dist[v], v));
			}
		}
	}
}

int main() {
	int n;
	char age, direction, city1, city2;
	int energy;
	char src, dst;
	while (true) {
		cin >> n;
		if (n == 0)
			break;

		vector<vector<Target>> graph(MAX);
		while (n--) {
			cin >> age >> direction >> city1 >> city2 >> energy;
			city1 -= 'A', city2 -= 'A';
			graph[city1].push_back(Target(energy, city2, age == 'Y'));
			if (direction == 'B')
				graph[city2].push_back(Target(energy, city1, age == 'Y'));
		}

		cin >> src >> dst;
		src -= 'A', dst -= 'A';
		vector<int> distFromSrc(MAX, INF);
		vector<int> distFromDst(MAX, INF);
		dijikstra(src, graph, distFromSrc, true); // NLog(MAX)
		dijikstra(dst, graph, distFromDst, false); // NLog(MAX)

		int minDist = INF;
		for (int i = 0; i < MAX; i++) { // O(MAX)
			if (distFromSrc[i] != INF && distFromDst[i] != INF && distFromSrc[i] + distFromDst[i] < minDist) {
				minDist = distFromSrc[i] + distFromDst[i];
			}
		}

		if (minDist != INF) {
			cout << minDist;
			for (int i = 0; i < MAX; i++) {
				if (distFromSrc[i] != INF && distFromDst[i] != INF && distFromSrc[i] + distFromDst[i] == minDist) {
					cout << " " << char(i + 'A');
				}
			}
			cout << endl;
		} else {
			cout << "You will never meet." << endl;
		}
	}

	return 0;
}
