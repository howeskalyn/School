// Kalyn Howes
// 2.18.21
// Lab 3
// Heap sort testing.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
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

void swap(int&, int&);
void MaxHeapify(Heap, int);
void BuildMaxHeap(Heap);
void HeapSort(Heap);
void printHeap(Heap);
bool isSorted(int[], int);

// other Heap functions not currently used
void MaxHeapInsert(Heap, int); 
void IncreaseKey(Heap, int, int); 

int main() {

    Heap A;
    A.length = 10;
    A.heap_size = A.length;
    A.arr = new int[A.length]; // points 'arr' to array of size A.length
    
    // sorted
    for (int i = 1; i <= A.length; i++) {
        //A.arr[i] = i;
        A[i] = i;
    }
    //*/

    /* sorted backwards
	 for (int i = 1; i <= A.length; i++)
        A.arr[i] = A.length - i + 1;
    */

	/* includes duplicates
	int temp = 0;
	for (int i = 1; i <= A.length; i += 2) {
		temp = (rand() % A.length) + 1;
		A.arr[i] = temp;
		A.arr[i + 1] = temp;
	}
   */

	/* random numbers
	 srand((unsigned) time(0));
	 for (int i = 1; i <= A.length; i++) {
	    A.arr[i] = (rand() % A.length) + 1;
	 }
    */

    // TIMING:
    printHeap(A);

    cout << "\n\nTime starts now: ";
	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();

    HeapSort(A);

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";  
    
    cout << "\nWas it sorted?" << endl;
	if (isSorted(A.arr, A.length) == 1)
		cout << "The array is sorted." << endl;
	else
		cout << "The array is NOT sorted." << endl;
    printHeap(A);

    delete A.arr;
    return 0;
}

// ------------------ FUNCIONS -------------------- //

// Exchanges the values of two integers sent into the function by reference. 
// Nothing is returned.
void swap(int &a, int &b)  {  
    int temp = a;  
    a = b;  
    b = temp;  
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

// Takes in an un-ordered array and creates a max-heap from the elements.
// Uses Θ(n) time.
void BuildMaxHeap(Heap A) {
    A.heap_size = A.length; // the whole array will be a heap when we’re done
    for (int i = (A.length / 2); i > 0; i--) { // down to 1  
        MaxHeapify(A, i);
    }
}

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


// Verifies if a given integer array is properly sorted - returns 0 if false & 1 if true
bool isSorted(int *arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

// ------ EXTRA FUNCTIONS -------- //
/*
// Takes in the heap and the new key to be inserted.
void MaxHeapInsert(Heap A, int key) {
    if (A.heap_size >= A.length)
        cout << "\nHeap length is smaller than the heap size." << endl;
    A.heap_size++;
    A[A.heap_size] = -1; // or infinity or NULL
    IncreaseKey(A, A.heap_size, key);
}

// Subroutine for MaxHeapInsert
// T(n) = theta(logn)
void IncreaseKey(Heap A, int i, int key) {
    // assume A[i] < key or throw error
    if (A[i] >= key)
        cout << "\nA[i] is NOT less than the key." << endl;
    while (i >= 0 && A[i] > A[(i/2) - 1]) {
        swap(A[i], A[(i/2) - 1]);
        i = (i/2) - 1;
    }
}*/

