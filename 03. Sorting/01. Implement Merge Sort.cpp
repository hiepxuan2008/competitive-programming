// Problem: Implement Merge Sort
// Author: Mai Thanh Hiep
// Complixity:
//			Time: O(NlogN)
//			Space: O(N)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void mergeSortHelper(vector<int>& arr, int left, int right, vector<int>& temp) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    mergeSortHelper(arr, left, mid, temp);
    mergeSortHelper(arr, mid + 1, right, temp);

    // merge arr[left, mid] and arr[mid+1, right] to temp[left, right]
    int i = left, j = mid + 1, k = left;
    while (i <= mid || j <= right) {
        if (i <= mid && (j == right + 1 || arr[i] < arr[j])) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // copy temp[left, right] into arr[left, right]
    for (int i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSort(vector<int>& arr) {
    vector<int> temp(arr.size());
    mergeSortHelper(arr, 0, arr.size() - 1, temp);
}

void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = { 9, 1, 5, 3, 7, 10 };
    mergeSort(arr);
    printArr(arr);

    return 0;
}