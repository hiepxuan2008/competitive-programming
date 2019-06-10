// Problem: Implement Heap Sort
// Author: Mai Thanh Hiep
// Complixity:
//			Time: O(NlogN)
//			Space: O(1)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void heapifyDown(vector<int>& arr, int i, int n) {
    int choose = i;
    int left, right;
    while (true) {
        left = i * 2 + 1;
        right = i * 2 + 2;

        if (left < n && arr[i] < arr[left])
            choose = left;
        if (right < n && arr[choose] < arr[right])
            choose = right;

        if (i == choose)
            break;
        swap(arr[i], arr[choose]);
        i = choose;
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max heap O(N)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, i, n);
    }

    // At this point, the largest item is stored at the root of the heap. 
    // Replace it with the last item of the heap followed by reducing the size of heap by 1. Finally, heapify down the root of tree.
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[i], arr[0]);
        heapifyDown(arr, 0, i);
    }
}

void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = { 9, 1, 5, 3, 10, 7 };
    heapSort(arr);
    printArr(arr);

    return 0;
}