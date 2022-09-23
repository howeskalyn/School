// Kalyn Howes
// 2.25.21
// Lab 4
// Template Class HeapQ - used to model a heap-based priority queue

#include "HeapQ.h"
#include <iostream>
#include <math.h>
#include <ctime> // for random reset

// constructor
template<typename T>
HeapQ<T>::HeapQ(int size, bool randkey, T defaultval) {

    heap_size = size;
    current_size = 0;
    arr = new HeapObj<T>[heap_size];

    // if randkey is true, the keys wil be randomized - otherwise an empty heap is created & data must be inserted
    if (randkey) {
        srand(time(NULL));
        for (int i = 0; i < heap_size; i++) {
            HeapObj<T> value;
            value.key = rand() % 1000; //creates a random intger that will be its priority
            
            value.data = defaultval;
            arr[i] = value;
            current_size++;
        }
        BuildHeap();
    }
    else {
        std::cout << " (an empty heap was made) " << std::endl;
    }
}

// destructor
template<typename T>
HeapQ<T>::~HeapQ() {
    delete[] arr;
}

// Builds the Heap
template<typename T>
void HeapQ<T>::BuildHeap() {
    for (int i = (current_size / 2); i >= 0; i--) { 
        MaxHeapify(i);
    }
}

// Extracts the maximum value from the Heap.
template<typename T>
T& HeapQ<T>::ExtractMax() {
    if (heap_size < 1)
        std::cerr << "Heap Underflow." << std::endl;

    arr[0].key = -1;
    swapPos(arr[0], arr[heap_size]);
    MaxHeapify(1);
    heap_size--;
    return arr[heap_size + 1].data;
}

// Performs maintenance on the heap to maintain the max-heap property
// This should take only Θ(log n) time on an array of length n
template<typename T>
void HeapQ<T>::MaxHeapify(int i) {
    int l = (2 * i);
    int r = (2 * i) + 1;

    // find the largest and swap with i
    int largest = i;
    if (l < current_size) 
        if (arr[l].key > arr[i].key)
            largest = l;
    if (r < current_size)
        if(arr[r].key > arr[largest].key)
            largest = r;

    if (i != largest) { // may have violated the heap property - recurse downward
        swapPos(arr[i], arr[largest]);
        MaxHeapify(largest);
    }
}

// Sees what data is the current top of the queue.
template <typename T>
int HeapQ<T>::Peek() {
    return arr[0].key;
}

// Inserts a new item into the heap.
template <typename T>
void HeapQ<T>::Insert(T A, int K) {

    // adds a new heap item and calls Increase-Key to put in the correct position
    if (current_size < heap_size) {
    
        arr[current_size].data = A; // or -infinity?
        arr[current_size++].key = K; // or -infinity?
        IncreaseKey(current_size - 1, K); //move the new key up the heap as needed.
        
        /*if (current_size > 1) {
            BuildHeap(); // cop out of using IncreaseKey... couldnt get it to work
        }*/

    } else
        std::cout << "Heap queue is full!" << std::endl;
}

/* Displays current contents of the heap, along with key data,
//      you may assume in this method that class T has an overloaded << operator
// (old print from Lab3 - indicies are off)
template<typename T>
void HeapQ<T>::Print() {
    int items = 1 ; // first level should only have 1 item
    int printed = 0 ; // number of items already printed

    for (int i = 1; i <= current_size; i++) { // for each item in the heap
        if (printed == 0 ) // new line if nothing is printed
            std::cout << "\n";

        std::cout << arr[i].key << ' ';
        printed++; // one element was printed so increase the variable

        if (printed == items) { // if the level is complete
            items *= 2 ; // next line will have twice as many items
            printed = 0 ; // reset number of printed items
        }
    }
}
*/

// Increases the key of a node at a particular location.
//      (private because the outside code will not know the array positions)
template<typename T>
void HeapQ<T>::IncreaseKey(int i, int K) {
    // not moving values to the 0th index (working except for that last swap)...
    
    // Increases the priority of the item at location i in the heap, the
    //      does a “reverse” Max-Heapify to move it upward accordingly
    if (K < arr[i].key) {
        std::cerr << "new key smaller than old key!" << std::endl;
        return;
    }
    arr[i].key = K;
    while (i >= 1 && arr[i / 2].key < arr[i].key) {
        // swap priorities & then swap the data
        swapPos(arr[i], arr[i / 2]);
        i = i / 2;
    }
}

// Expands the internal array if needed by the user.
template<typename T>
void HeapQ<T>::Expand(int n) {
    for (int i = 0; i < n; i++) 
        current_size++;
}

// Exchanges the values of two integers sent into the function by reference. 
// Nothing is returned.
//void swap(int &a, int &b)  {  
//    int temp = a;  
//    a = b;  
//    b = temp;  
//} 

// Exchanges the positions of heapObj items
template<typename T>
void HeapQ<T>::swapPos(HeapObj<T> &A, HeapObj<T> &B) {
    HeapObj<T> temp;
    temp.data = A.data;
    temp.key = A.key;
    
    A.data = B.data;
    A.key = B.key;

    B.data = temp.data;
    B.key = temp.key;
}

template<typename T>
void HeapQ<T>::OtherPrint() {

    int rowcalc = 1; // calculated node index - marks the end of a level 
    int level = 0;

    if (current_size > 0) {
            std::cout << "\nLevel: " << level + 1 << "\n---------" << std::endl; 
        for (int i = 0; i < current_size; i++) {
            //time to calculate the new max index of this level    
            if (i >= rowcalc) {
                std::cout << "\nLevel: " << level + 2 << "\n---------" << std::endl; 
                rowcalc += pow(2, ++level);
            }
            else if(i != 0)
                std::cout << std::endl;

            std::cout << "Node #" << i + 1 << ":" << std::endl;
            std::cout << "Priority: " << arr[i].key << std::endl;
            std::cout << "Data: " << arr[i].data << std::endl;
        }
    }
    else
        std::cout << "The Heap is empty..." << std::endl;

}
