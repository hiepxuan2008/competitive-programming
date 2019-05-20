// Problem: Implement Quick Sort
// Author: Mai Thanh Hiep
// Complixity:
//			Time: O(NlogN)
//			Space: O(1)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
	if (left >= right)
		return;

	int i = left, j = right;
	int pivot = arr[(left + right) / 2]; // if pivot always be greatest or smallest element of array then time complexity will be O(N^2)
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++, j--;
		}
	}

	quickSort(arr, left, j);
	quickSort(arr, i, right);
}

void quickSort(vector<int>& arr) {
	quickSort(arr, 0, arr.size() - 1);
}

void printArr(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	vector<int> arr = { 9, 1, 5, 3, 10, 7 };
	quickSort(arr);
	printArr(arr);

	return 0;
}