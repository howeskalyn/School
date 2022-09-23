/* Kalyn Howes
 1.28.21
 Lab 1: Comparison of sorting algorithms
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int* BubbleSort(int*, int, int&);
int* InsertionSort(int*, int, int&);
int* SelectionSort(int*, int, int&);
bool isSorted(int*, int);

int main() {

	// keeps track of number swaps made in each sort
	int bSwaps = 0, iSwaps = 0, sSwaps = 0;

	// ARRAY SET UP:
	int size = 50000;
	int arrB[size];
	int arrI[size];
	int arrS[size];

	// Array types:
	/* already sorted
	for (int i = 0; i < size; i++) {
		arrB[i] = i;
	}
	/* sorted backwards
	for (int i = 0; i < size; i++) {
		arrB[i] = size - i;
	}*/
	// includes duplicates
	for (int i = 0; i < size; i += 2) {
		arrB[i] = i;
		arrB[i + 1] = i;
	}
	/* random numbers
	srand((unsigned) time(0));
	for (int i = 0; i < size; i++) {
		arrB[i] = (rand() % 100) + 1;
	}*/

	// copies array twice to try with other sorts
	for (int i = 0; i < size; i++) {
		arrI[i] = arrB[i];
		arrS[i] = arrB[i];
	}

	// ------- SORTING & TIMING --------

	cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();

	BubbleSort(arrB, size, bSwaps); // sorting algorithms
	//InsertionSort(arrI, size, iSwaps);
	//SelectionSort(arrS, size, sSwaps);

	cout << "Is it sorted?" << endl;
	if (isSorted(arrB, size) == 1)
		cout << "The array is sorted." << endl;
	else
		cout << "The array is NOT sorted." << endl;
	cout << "# of swaps: " << bSwaps << endl;

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";
}

// BubbleSort: takes in an array of integers and its size and Bubble sorts the array.
int* BubbleSort(int *arr, int size, int &bSwaps) {

	int temp = 0;

	for (int i = 0; i < size - 1; i++) {

		for (int j = 0; j < size - i - 1; j++) {

			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				bSwaps++;
			}
		}
	}

	return arr;
}

// InsertionSort: takes in an array of integers and its size and Insertion sorts the array.
int* InsertionSort(int *arr, int size, int &iSwaps) {
	int j = 0, key = 0;

	for (int i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;

		// move elements of arr that are greater than key to one pos higher
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
			iSwaps++;
		}

		arr[j + 1] = key;
	}

	return arr;
}

// SelectionSort: takes in an array of integers and its size and Selection sorts the array.
int* SelectionSort(int *arr, int size, int &sSwaps) {
	int minI = 0, temp = 0; // minI = minimum index

	for (int i = 0; i < size - 1; i++) {
		minI = i;

		for (int j = i + 1; j < size; j++)
			if (arr[j] < arr[minI])
				minI = j;

		// swap
		temp = arr[minI];
		arr[minI] = arr[i];
		arr[i] = temp;
		sSwaps++;
	}

	return arr;
}

// isSorted: verifies if a given integer array is properly sorted - returns 0 if false & 1 if true
bool isSorted(int *arr, int size) {

	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;

}
