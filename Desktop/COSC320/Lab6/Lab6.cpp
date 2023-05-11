/* 
* Kalyn Howes
* 3.18.21
* Lab6 - randomized quicksort: comparisons to quicksort, mergesort, & heapsort
*/

#include <iostream>
#include <stdlib.h> // for rand
#include <time.h> // for time reset
#include <cstdlib> // timing
#include <ctime> // timing
#include <chrono> // timing
using namespace std;

// struct to hold the heap array, length, and size
struct Heap {
    int * arr; // pointer to 'arr'
    int length; // the size of arr
    int heap_size; // changes based on which portion of arr is a valid heap

// overriding the [] operator to re-index the array from 1 (instead of 0)
// when given an [], it returns an int reference to assign into the structure
    int& operator[](int i) {
        if ( i >= 1 && i <= length)
            return arr[i - 1]; // so A[1] is the first and A[n] is the last
        else {
            cerr << "\n1 <= i <= length is not true." << endl;
            //return -1;
        }
    }
};

// --- PROTOTYPES ---
// helpers
int* shuffle(int);
void swap(int&, int&);
bool isSorted(int[], int);
void printArr(int*, int);

// hiring
int hire(int[], int);

// quicksort
void quicksort(int*, int, int);
int partition(int*, int, int);
void randomQuicksort(int*, int, int);

// mergesort
void mergesort(int[], int, int);
void merge(int[], int, int, int);

// heapsort
void MaxHeapify(Heap, int);
void BuildMaxHeap(Heap);
void HeapSort(Heap);
void printHeap(Heap);

int main() {
    srand (time(NULL)); // reset
    
    // ------- PART 1: HIRING ALGORITHM --------
    int numCans = 50; // number of candidates
    int *arr = new int[numCans];

    // c) Do the below experiment about 10 times for each different n and report the average
    float count = 0; // holds number of times an assistant is replaced
    float sum = 0; // holds total number of times an assistant is replaced

    int runs = 30; // number of times to run the hiring algorithm
    for (int t = 0; t < runs; t++) {
        cout << "\n ---- RUN " << t + 1 << " ---- " << endl;

        // a) Shuffle the elements {1, 2, . . . , n} and interpret them as the relative ranks of the candidate assistants
        arr = shuffle(numCans); // creates & shuffles a new array
    
        // b) Run the Hire-Assistant algorithm and count the number of times that the current assistant is replaced by a better one
        count = hire(arr, numCans);
        cout << "\n\nNumber of replacements: " << count << endl;
        sum += count;
        cout << "Sum now equals: " << sum << endl;
    }
    float avg = (float)sum / (float)runs; // find average by summing up each run and dividing by number of trials
    cout << "\nAverage replacements for size " << numCans << ": " << avg << endl;
    //*/
    

    /* ------- PART 2: TIMING SORTS -------
    // average the times for the 20 trials to get an estimate of the expected running time for n elements of each algorithm

    float sumTime = 0; // holds total amount of time taken to sort
    float avgTime = 0; // holds average time of sorts = sumTime / k times

    for (int n = 10000; n <= 1010000; n+=50000) {
        cout << "\n --- NEW LOOP: N = " << n  << " --- " << endl;
        int *A = new int[n];
        for (int k = 1; k < 10; k++) {
            // use shuffle to generate an array of size n
            A = shuffle(n);
            
            // time each sorting algorithm on (a copy of) that array
	        // The "auto" type determines the correct type at compile-time
	        auto start = std::chrono::system_clock::now();
 
            // quicksort:
            quicksort(A, 0, n - 1); 

            // randomized quicksort:
            // randomQuicksort(A, 0, n - 1); 

            // mergesort:
            // mergesort(A, 0, n - 1); 

            /* heapsort:
            Heap H;
            H.length = n;
            H.heap_size = H.length;
            H.arr = new int[H.length]; // points 'arr' to array of size A.length
            // fill with random numbers
	        for (int i = 1; i <= H.length; i++) {
	            H.arr[i] = (rand() % H.length) + 1;
	        }
            HeapSort(H); */

            /* debuggin'
	        cout << "Is it sorted?" << endl;
	        if (isSorted(A, n) == 1)
		        cout << "The array is sorted." << endl;
	        else
		        cout << "The array is NOT sorted." << endl;*/

            /* 
            auto end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            sumTime += elapsed_seconds.count();
        }
        avgTime = (float) sumTime / (float) 10; // number of times the inner loop is run
        cout << "Average time for n = " << n << " is: " << avgTime << endl;
    }*/

    return 0;
}

// ------------------------ FUNCTIONS ------------------------

// -------- HELPERS --------
// generates an array of all numbers from 1 through n in a random order
// for each element i = 1 to n, swap i with a random element from {i, i + 1, . . . , n}
int* shuffle(int n) {
    int *arr = new int[n];

    // fill array 1 to n:
    int j = 1;
    for (int i = 0; i < n; i++) {
        arr[i] = j;
        j++;
    }

    // testing/debug
    //cout << "\nOriginal array:" << endl;
    //printArr(arr, n);

    // swap values around:
    int s = 0; // index to swap
    for (int i = 0; i < n; i++) {
        s = rand() % n; // set s to random index within array size
        swap(arr[i], arr[s]);
    }

    // testing/debug
    //cout << "\nShuffled array:" << endl;
    //printArr(arr, n);

    return arr;
}

// Exchanges the values of two integers sent into the function by reference. 
// Nothing is returned.
void swap(int &a, int&b) {
    int temp = a;
    a = b;
    b = temp;
}

// Verifies if a given integer array is properly sorted - returns 0 if false & 1 if true
bool isSorted(int *arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

// prints a given array - must send in size with it
void printArr(int *arr, int size) {
    //cout << "\nPrinting Array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

// -------- HIRING --------
// takes in a list of candidates and the size of the list
// returns the number of times that the current assistant is replaced by a better one
int hire(int arr[], int n) {
    int count = 0;
    int best = 0;
    best = arr[0]; // interview & hire first candidate 

    for (int i = 1; i < n; i++) {
        if (arr[i] > best) {
            best = arr[i];
            count++;
        }
    }
    return count;
}

// -------- QUICKSORT --------
// Sorts an integer array using the QuickSort algorithm. 
// Requires the array, the start index, and the end index to be sent in.
void quicksort(int* arr, int start, int end) {
    int piv = 0; // hold pivot location
    if (start < end) {
        piv = partition(arr, start, end);
        quicksort(arr, start, piv - 1);
        quicksort(arr, piv + 1, end);
    }
}

// Subroutine to choose a pivot and move the pivot to the correct location of the array.
// Requires the array, the start index, and the end index to be sent in.
// The index of where it ends up in the array is returned.
// (should only need Θ(n) time) 
int partition(int* arr, int start, int end) {
    int piv = arr[end]; // pivot value
    int loc = start - 1; // tracks current position the pivot needs to be
    for (int i = start; i < end; i++) {
        if (arr[i] <= piv) {  // A[i] needs to be on the left of the pivot
            loc = loc + 1;
            swap(arr[loc], arr[i]);
        }
    }
    swap(arr[loc + 1], arr[end]);  // put the pivot in the correct location
    return (loc + 1);
}

// Randomized verison of QuickSort
void randomQuicksort(int* arr, int start, int end) {
    if (start < end) {
        int p = start + rand() % (end - start); // chooses random index to pivot
        swap(arr[start], arr[p]);
        int pivot = partition(arr, start, end);
        randomQuicksort(arr, start, pivot - 1);
        randomQuicksort(arr, pivot + 1, end);
    }
}

// -------- MERGESORT --------
// Sorts an integer array using the MergeSort Algorithm.
// Requires the array, the start index, and the end index to be sent in.
void mergesort(int arr[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2; // find middle

        mergesort(arr, start, mid); // sort first part
        mergesort(arr, mid + 1, end); // sort second part
        merge(arr, start, mid, end); // merge parts together
    }
}

// Merges two subarrays of the main int array.
// The first subarray starts at index 'l' and ends at index 'm'
// The second subarray starts at index 'm+1' and ends at index 'n'
void merge(int arr[], int l, int k, int p) {

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
        if (left[idx] <= right[idx2]) {
            arr[idxM] = left[idx];
            idx++;
        }
        else {
            arr[idxM] = right[idx2];
            idx2++;
        }
        idxM++;
    }
 
    // copy remaining elements of left subarray
    while (idx < m) {
        arr[idxM] = left[idx];
        idx++;
        idxM++;
    }
    // copy remaining elements of right subarray
    while (idx2 < n) {
        arr[idxM] = right[idx2];
        idx2++;
        idxM++;
    }
}

// -------- HEAPSORT --------
// Takes in an array and sorts it using the above subroutines
// This procedure should take Θ(n log n) time. 
void HeapSort(Heap A) {
    // ensure array is a valid heap - largest element must be A[1]
    BuildMaxHeap(A);
    for (int i = A.length; i > 1; i--) { // down to 2
        // A[i] is the largest among A[1, . . . , i], so move it
        // to the back, and consider it removed from the heap
        //swap(A.arr[1], A.arr[i]);
        swap(A[1], A[i]);
        A.heap_size--;
        // moved one of the smaller elements to the root, so we have to clean up
        MaxHeapify(A, 1);
    }
}

// Takes in an un-ordered array and creates a max-heap from the elements.
// Uses Θ(n) time.
void BuildMaxHeap(Heap A) {
    A.heap_size = A.length; // the whole array will be a heap when we’re done
    for (int i = (A.length / 2); i > 0; i--) { // down to 1  
        MaxHeapify(A, i);
    }
}

// Performs maintenance on the heap to maintain the max-heap property
// This should take only Θ(log n) time on an array of length n
void MaxHeapify(Heap A, int i) {
    int l = (2 * i);
    int r = (2 * i) + 1;

    // find the largest and swap with i
    int largest = 1;
    //if (l <= A.heap_size && A.arr[l] > A.arr[i])
    if (l <= A.heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;

    //if (r <= A.heap_size && A.arr[r] > A.arr[largest])
    if (r <= A.heap_size && A[r] > A[largest])
        largest = r;

    if (i != largest) { // may have violated the heap property - recurse downward
        //swap(A.arr[i], A.arr[largest]);
        swap(A[i], A[largest]);
        MaxHeapify(A, largest);
    }
}

// Takes an array and prints out the array's elements as a heap (in a left-aligned form by level).
void printHeap(Heap A) {

    int items = 1 ; // first level should only have 1 item
    int printed = 0 ; // number of items already printed

    for (int i = 1; i <= A.length; i++) { // for each item in the heap
        if (printed == 0 ) // new line if nothing is printed
            cout << "\n";

        cout << A[i] << ' ' ;
        printed++; // one element was printed so increase the variable

        if (printed == items) { // if the level is complete
            items *= 2 ; // next line will have twice as many items
            printed = 0 ; // reset number of printed items
        }
    }
}






