// Problem: Roy and Trending Topics
// Link: https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/roy-and-trending-topics-1/description/
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Record {
    long long id;
    long long change;
    long long newScore;
};

struct greaterComparator {
    bool operator() (const Record& r1, const Record& r2) const {
    if (r1.change != r2.change)
        return r1.change > r2.change;
    else
        return r1.id > r2.id;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
	cin >> n;
    priority_queue<Record, vector<Record>, greaterComparator> minHeap;
    long long topicId, currentScore, posts, likes, comments, shares;
    long long newScore, change;
    for (int i = 0; i < n; i++) {
        cin >> topicId >> currentScore >> posts >> likes >> comments >> shares;
        newScore = posts * 50 + likes * 5 + comments * 10 + shares * 20;
        change = newScore - currentScore;

        if (minHeap.size() < 5) {
            minHeap.push((Record) {topicId, change, newScore});
        }
        // if we found a greater record, remove current min record, push new one to our minHeap
        else if ((minHeap.top().change < change) || (minHeap.top().change == change && minHeap.top().id < topicId)) {
            minHeap.pop();
            minHeap.push((Record) {topicId, change, newScore});
        }
    }

    // convert heap to vector for sorting
    vector<Record> records;
    while (!minHeap.empty()) {
        records.push_back(minHeap.top());
        minHeap.pop();
    }

    // Sort in decreasing by change, id
    sort(records.begin(), records.end(), greaterComparator());

    // print results
    for (int i = 0; i < records.size(); i++) {
        cout << records[i].id << " " << records[i].newScore << endl;
    }

    return 0;
}
