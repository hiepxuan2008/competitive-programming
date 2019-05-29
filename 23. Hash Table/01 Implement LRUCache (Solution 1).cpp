// Problem: Implement LRU Cache
// Author: Mai Thanh Hiep
// Complexity: 
//		set: O(1)
//		get: O(1)

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class LRUCache {
	int capacity;
	list<int> dll; // first of list -> least used, last of list -> recent used
	unordered_map<int, pair<string, list<int>::iterator>> cache;

public:
	LRUCache(int _capacity) {
		capacity = _capacity;
	}

	bool isFull() {
		return cache.size() == capacity;
	}

	void set(int key, string value) {
		if (cache.find(key) == cache.end() && isFull()) { // insert new one && lruCache is full
			// pick victim (least recently used) to remove
			int removeKey = dll.front();
			cache.erase(removeKey); // clear from cache
			dll.pop_front(); // remove key from list
		}
		else if (cache.find(key) != cache.end()) {
			dll.erase(cache[key].second); // remove key from list
		}

		// add new one to lruCache
		dll.push_back(key);
		cache[key] = make_pair(value, prev(dll.end()));
	}

	string get(int key) {
		if (cache.find(key) == cache.end()) {
			return "NULL";
		}

		pair<string, list<int>::iterator> node = cache[key];
		dll.erase(node.second);
		dll.push_back(key);
		return node.first;
	}
};

int main() {
	LRUCache lruCache(3);
	lruCache.set(1, "John");			// [{1, John}]
	lruCache.set(2, "Usha");			// [{1, John}, {2, Usha}]
	lruCache.set(3, "Summer");			// [{1, John}, {2, Usha}, {3, Summer}]
	lruCache.set(4, "Bella");			// [{2, Usha}, {3, Summer}, {4, Bella}]
	cout << lruCache.get(2) << endl;	// Usha		[{3, Summer}, {4, Bella}, {2, Usha}]
	cout << lruCache.get(1) << endl;	// NULL		[{3, Summer}, {4, Bella}, {2, Usha}]
	lruCache.set(5, "Alice");			// [{4, Bella}, {2, Usha}, {5, Alice}]
	cout << lruCache.get(3) << endl;	// NULL		[{4, Bella}, {2, Usha}, {5, Alice}]
	cout << lruCache.get(4) << endl;	// Bella	[{2, Usha}, {5, Alice}, {4, Bella}]

	return 0;
}