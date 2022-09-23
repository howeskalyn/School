//============================================================================
// Name        : QuickSortTemplate.cpp
// Description : A template version of the QuickSort algorithm that will work
//				 with any data type. Demonstrated with a driver function.
// Author      : Kalyn Howes
// Date		   : 11/3/20
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// prototyping
template<class T>
void quickSort(T[], int, int);
template<class T>
int split(T[], int, int);

int main() {
	// random array created
	srand((unsigned)time(0));

	int size = 10;
	int arr[size];
	for (int i = 0; i < size; i++) {
		arr[i] = (rand() % 100) + 1;
	}

	// print array
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;

	// sort the array using quicksort (templated)
	quickSort(arr, 0, size - 1);

	// print the sorted array
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;

	// try array of doubles
	double darr[5] = { 2.3, 4.5, 8.56, 1.34, 6.90 };
	// print
	for (int i = 0; i < 5; i++)
		cout << darr[i] << " ";
	cout << endl;
	// sort
	quickSort(darr, 0, 4);
	// print sorted array
	for (int i = 0; i < 5; i++)
		cout << darr[i] << " ";
	cout << endl;

	// try array of chars
	char carr[5] = {'a', 'c', 'p', 'l', 'b'};
	// print
	for (int i = 0; i < 5; i++)
		cout << carr[i] << " ";
	cout << endl;
	// sort
	quickSort(carr, 0, 4);
	// print sorted array
	for (int i = 0; i < 5; i++)
		cout << carr[i] << " ";
	cout << endl;

	return 0;
}

// QuickSort function:
// parameters: array of templates & start and end values
template<class T>
void quickSort(T arr[], int start, int end) {
	if (start < end) {

		// split up the array and get the pivot point
		int s = split(arr, start, end);

		// sort the part before the pivot
		quickSort(arr, start, s - 1);

		// sort the part after the pivot
		quickSort(arr, s + 1, end);
	}
}

// Split function:
// parameters: array of templates & start and end values
template<class T>
int split(T arr[], int start, int end) {

	// the pivot is the start of the range to be split
	T pivotValue = arr[start];
	int pivotPosition = start;

	// rearrange the rest of the array elements to split the range from start to end
	for (int pos = start + 1; pos <= end; pos++) {
		if (arr[pos] < pivotValue) {

			// swap current item with item to the right of pivot
			swap(arr[pivotPosition + 1], arr[pos]);
			// swap current item with pivot element
			swap(arr[pivotPosition], arr[pivotPosition + 1]);
			// adjust the pivot index so it stays with pivot element
			pivotPosition++;
		}
	}
	return pivotPosition;
}
