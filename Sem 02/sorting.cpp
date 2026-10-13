#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int start, int mid, int end) {
	std::vector<int> left(mid - start), right(end - mid + 1);
	for (int i = start; i < mid; i++) left[i - start] = arr[i];
	for (int i = mid; i <= end; i++) right[i - mid] = arr[i];

	int i = 0, j = 0, k = start;
	while (i < left.size() && j < right.size()) {
		if (left[i] <= right[j]) arr[k++] = left[i++];
		else arr[k++] = right[j++];
	}
	while (i < left.size()) {
		arr[k++] = left[i++];
	}
	while (j < right.size()) {
		arr[k++] = right[j++];
	}
}

void mergeSort(std::vector<int>& arr, int start, int end) {
	if (start >= end) return;

	int mid = end + (start - end) / 2;
	mergeSort(arr, start, mid - 1);
	mergeSort(arr, mid, end);
	merge(arr, start, mid, end);
}

int partition(std::vector<int>& arr, int start, int end) {
	int pivot = arr[end];
	int pivotIndex = start;
	for (int i = start; i < end; i++) {
		if (arr[i] < pivot) std::swap(arr[i], arr[pivotIndex++]);
	}
	std::swap(arr[end], arr[pivotIndex]);
	return pivotIndex;
}

void quickSort(std::vector<int>& arr, int start, int end) {
	if (start >= end) return;

	int partitionIndex = partition(arr, start, end);
	quickSort(arr, start, partitionIndex - 1);
	quickSort(arr, partitionIndex + 1, end);
}

int main() {
	{
		std::vector<int> v = { 4, 3, 1, 9, 5, 7, 2, 10, 6 };
		quickSort(v, 0, v.size() - 1);
	}
	{
		std::vector<int> v = { 38, 27, 43, 10, 15 };
		mergeSort(v, 0, v.size() - 1);
	}
}
