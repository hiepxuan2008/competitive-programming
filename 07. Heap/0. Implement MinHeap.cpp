// Problem: Implement Min Heap - Find K_th largest element of array
// Author: Mai Thanh Hiep
/* Complexity: 
        Push: O(K)
        Pop: O(K)
        O(NlogK)
        N is size of array, K is the size of the heap
*/

#define _CRT_SECURE_NO_WARNINGS 0

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class MinHeap {
    int capacity;
    int _size;
    int* arr;

    int getLeft(int index) {
        return index * 2 + 1;
    }

    int getRight(int index) {
        return index * 2 + 2;
    }

    int getParent(int index) {
        if (index == 0)
            return -1;
        return (index - 1) / 2;
    }

    void heapifyUp(int index) {
        int parent = getParent(index);
        while (parent != -1 && arr[parent] > arr[index]) {
            swap(arr[parent], arr[index]);
            index = parent;
            parent = getParent(index);
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int select = index;
            int left = getLeft(index);
            int right = getRight(index);
            if (left < _size && arr[left] < arr[select])
                select = left;
            if (right < _size && arr[right] < arr[select])
                select = right;

            if (select == index)
                break;
            else {
                swap(arr[select], arr[index]);
                index = select;
            }
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        arr = new int[capacity];
        _size = 0;
    }

    ~MinHeap() {
        delete[] arr;
    }

    int size() {
        return _size;
    }

    int top() {
        return arr[0];
    }

    void push(int value) {
        arr[_size++] = value;
        heapifyUp(_size - 1);
    }

    void pop() {
        if (_size == 0)
            return;

        swap(arr[0], arr[--_size]);
        heapifyDown(0);
    }

    void reset() {
        _size = 0;
    }
};

int findKthLargestElementOfArray(const vector<int>& arr, int k) {
    MinHeap minHeap(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        if (minHeap.size() < k) {
            minHeap.push(arr[i]);
        } else if (arr[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }

    return minHeap.top();
}

int main() {
    vector<int> test = { 3,2,1,5,6,4 };
    int k = 2;

    cout << findKthLargestElementOfArray(test, k) << endl;

    return 0;
}