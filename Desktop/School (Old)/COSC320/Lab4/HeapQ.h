// Kalyn Howes
// 2.25.21
// Lab 4
// Template Class, 'HeapQ' header file - used to model a heap-based priority queue

#ifndef HEAPQ_H_
#define HEAPQ_H_

template <class T> 

class HeapQ {
    
public:
    // class uses an array of struct objects to hold the entire heap
    // individual nodes are a HeapObj
    template <typename H>
    struct HeapObj {
        H data;
        int key;
    };

    // maintain a dynamic array in HeapQ class:
    HeapObj<T> *arr;

	HeapQ(int, bool, T); // constructor
	~HeapQ(); // destructor

    // Public Heap operations:
    void BuildHeap();
    T& ExtractMax();
    void MaxHeapify(int);
    int Peek();
    void Insert(T, int);
    //void Print();
    void OtherPrint();

    //void swap(int, int);
    void swapPos(HeapObj<T>&, HeapObj<T>&);

    template<typename J>
    friend std::ostream& operator<< (std::ostream& os, const HeapQ<J>& t);

    inline int getCurSize() { return current_size; }
    inline int getHeapSize() { return heap_size; }
private:
    // need private variables to track heap size & current size of the array
    int heap_size;
    int current_size;

    // Private Heap operations:
    void IncreaseKey(int, int);
    void Expand(int);
};


template<typename T>
std::ostream& operator<< (std::ostream& os, HeapQ<T>& h) {
    if(h.getCurSize() > 0)
        h.OtherPrint(); //do print generation divisions
    else
        std::cout << "The heap is empty." << std::endl;

    std::cout << "\nMax Heap Size: " << h.getHeapSize() << std::endl;
    return os;
}
#endif /* HEAPQ_H_ */
