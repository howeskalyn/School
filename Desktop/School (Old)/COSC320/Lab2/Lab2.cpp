// Kalyn Howes
// 2.11.21
// Lab 2
// Quicksort and Mergesort run time testing.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void swap(int&,int&);
long quicksort(int*, int, int);
int partition(int*, int, int, long&);
void mergesort(int[], int, int, long&);
long merge(int[], int, int, int);
bool isSorted(int[], int);

int main() {

    // create integer array to test
    int size = 100;
	int *arr;
    arr = new int[size];
    long c = 0; // comparisons made duirng sorting

    // array types:
	// already sorted
	 for (int i = 0; i < size; i++)
	    arr[i] = i;

	/* sorted backwards
	 for (int i = 0; i < size; i++)
	    arr[i] = size - i;
    
	// includes duplicates
	int temp = 0;
	for (int i = 0; i < size - 1; i += 2) {
		temp = (rand() % 100) + 1;
		arr[i] = temp;
		arr[i + 1] = temp;
	}
	//  random numbers
	 srand((unsigned) time(0));
	 for (int i = 0; i < size; i++) {
	 arr[i] = (rand() % 100) + 1;
	 }

    	*/
    // timing:
    cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();
 
	//c = quicksort(arr, 0, size - 1);
    	mergesort(arr, 0, size - 1, c);

	cout << "Is it sorted?" << endl;
	if (isSorted(arr, size) == 1)
		cout << "The array is sorted." << endl;
	else
		cout << "The array is NOT sorted." << endl;

	cout << "# of comparisons: " << c << endl;

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";  

    delete arr;
    return 0;
}

// --------- FUNCTIONS ----------

// Exchanges the values of two integers sent into the function by reference. 
// Nothing is returned.
void swap(int &a, int &b)  {  
    int temp = a;  
    a = b;  
    b = temp;  
}  

// Sorts an integer array using the QuickSort algorithm. 
// Requires the array, the start index, and the end index to be sent in.
// The number of comparisons made is returned.
long quicksort(int* arr, int start, int end) {
    int piv = 0; // hold pivot location
    long compares = 0; // holds number of comparisons made
    if (start < end) {
        compares++;
        piv = partition(arr, start, end, compares);
        quicksort(arr, start, piv - 1);
        quicksort(arr, piv + 1, end);
    }
}

// Subroutine to choose a pivot and move the pivot to the correct location of the array.
// Requires the array, the start index, and the end index and the number of comparisons made to be sent in.
// The index of where it ends up in the array is returned.
// (should only need Θ(n) time) 
int partition(int* arr, int start, int end, long &compares) {
    int piv = arr[end]; // pivot value
    int loc = start - 1; // tracks current position the pivot needs to be
    for (int i = start; i < end; i++) {
        compares++;
        if (arr[i] <= piv) {  // A[i] needs to be on the left of the pivot
            loc = loc + 1;
            swap(arr[loc], arr[i]);
        }
    }
    swap(arr[loc + 1], arr[end]);  // put the pivot in the correct location
    return (loc + 1);
}

// Sorts an integer array using the MergeSort Algorithm.
// Requires the array, the start index, and the end index to be sent in.
// The number of comparisons that occurred are returned.
void mergesort(int arr[], int start, int end, long &compares) {
    if (start < end) {
        compares++;
        int mid = (start + end) / 2; // find middle

        mergesort(arr, start, mid, compares); // sort first part
        mergesort(arr, mid + 1, end, compares); // sort second part
        compares += merge(arr, start, mid, end); // merge parts together
    }
}

// Merges two subarrays of the main int array.
// The first subarray starts at index 'l' and ends at index 'm'
// The second subarray starts at index 'm+1' and ends at index 'n'
// Returns number of comparisons made.
long merge(int arr[], int l, int k, int p) {

    long compares = 0; // tracks number of comparisons
    int m = k - l + 1; // length of first subarray
    int n = p - k; // length of second subarray

    int left[m], right[n]; // temp arrays
 
    // copy elements to temp arrays
    for (int i = 0; i < m; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n; j++)
        right[j] = arr[k + 1 + j];
 
    // put the temp arrays back into arr
    int idx = 0; // index of first array
    int idx2 = 0; // index of second array
    int idxM = l; // index of merged array
 
    while (idx < m && idx2 < n) {
        compares++;
        if (left[idx] <= right[idx2]) {
            //compares++;
            arr[idxM] = left[idx];
            idx++;
        }
        else {
            //compares++;
            arr[idxM] = right[idx2];
            idx2++;
        }
        idxM++;
    }
 
    // copy remaining elements of left subarray
    while (idx < m) {
        compares++;
        arr[idxM] = left[idx];
        idx++;
        idxM++;
    }
    // copy remaining elements of right subarray
    while (idx2 < n) {
        compares++;
        arr[idxM] = right[idx2];
        idx2++;
        idxM++;
    }
    return compares;
}

// Verifies if a given integer array is properly sorted - returns 0 if false & 1 if true
bool isSorted(int *arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}
