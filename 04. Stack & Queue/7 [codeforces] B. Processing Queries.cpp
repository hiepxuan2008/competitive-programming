// Problem: B. Processing Queries
// Link: https://codeforces.com/problemset/problem/644/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>
using namespace std;

#define MAX 200000
long long finishAt[MAX];

struct Query {
    int id;
    int processDuration;

    Query(int _id, int _processDuration) : id(_id), processDuration(_processDuration) {};
};

int main() {
    int n, maxQueueSize;
    scanf("%d %d", &n, &maxQueueSize);

    queue<Query> q;
    long long t = 0; // max: n*t -> max 2*10^5*10^9

    int arrivalTime, processDuration;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arrivalTime, &processDuration);

        // Pick a query in queue and process it if server is free
        while (!q.empty() && t <= arrivalTime) {
            Query top = q.front();
            q.pop();
            t += top.processDuration;
            finishAt[top.id] = t;
        }

        t = max(t, (long long)arrivalTime);

        // Add new query to the end of the queue if queue is not full
        if (q.size() < maxQueueSize) {
            q.push(Query(i, processDuration));
        }
        // Reject new query if queue is full
        else {
            finishAt[i] = -1;
        }
    }

    while (!q.empty()) {
        Query top = q.front();
        q.pop();
        t += top.processDuration;
        finishAt[top.id] = t;
    }

    for (int i = 0; i < n; i++)
        printf("%lld ", finishAt[i]);
    printf("\n");

    return 0;
}
