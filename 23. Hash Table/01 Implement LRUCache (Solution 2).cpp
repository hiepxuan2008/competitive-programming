// Problem: Implement LRU Cache
// Author: Mai Thanh Hiep
// Comment: Manually implement Double Linked List
// Complexity: 
//		set: O(1)
//		get: O(1)

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    int key;
    string value;
    Node* prev;
    Node* next;

    Node() {
        prev = next = NULL;
    }

    Node(int _key, string _value) : key(_key), value(_value) {
        prev = next = NULL;
    }
};

struct DoubleLinkedList {
    Node* head;
    Node* tail;

    DoubleLinkedList() {
        head = tail = NULL;
    }

    Node* front() {
        return head;
    }

    void erase(Node* node) {
        if (node == NULL || isEmpty())
            return;

        if (node == head) {
            pop_front();
            return;
        }

        if (node == tail) {
            pop_back();
            return;
        }

        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    void push_front(Node* node) {
        if (isEmpty()) {
            node->next = node->prev = NULL;
            head = tail = node;
            return;
        }

        node->next = head;
        node->prev = NULL;
        head->prev = node;
        head = node;
    }

    void push_back(Node* node) {
        if (isEmpty()) {
            push_front(node);
            return;
        }

        node->prev = tail;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    Node* pop_front() {
        if (isEmpty())
            return NULL;

        if (head == tail) {
            Node* node = head;
            head = tail = NULL;
            return node;
        }

        Node* node = head;
        head = node->next;
        head->prev = NULL;
        return node;
    }

    Node* pop_back() {
        if (isEmpty())
            return NULL;

        if (head == tail) {
            Node* node = head;
            head = tail = NULL;
            return node;
        }

        Node* node = tail;
        tail = node->prev;
        tail->next = NULL;
        return node;
    }

    bool isEmpty() {
        return head == NULL;
    }

    ~DoubleLinkedList() {
        Node* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class LRUCache {
    int capacity;
    DoubleLinkedList dll; // first of list -> least used, last of list -> recent used
    unordered_map<int, Node*> cache;

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
            Node* head = dll.front();
            cache.erase(head->key); // clear from cache
            dll.erase(head);
            delete head;
        } else if (cache.find(key) != cache.end()) {
            dll.erase(cache[key]); // remove node from dll
        }

        // add new one to lruCache
        Node* newNode = new Node(key, value);
        dll.push_back(newNode);
        cache[key] = newNode;
    }

    string get(int key) {
        if (cache.find(key) == cache.end()) {
            return "NULL";
        }

        Node* node = cache[key];
        string value = node->value;
        dll.erase(node);
        dll.push_back(node);
        return node->value;
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