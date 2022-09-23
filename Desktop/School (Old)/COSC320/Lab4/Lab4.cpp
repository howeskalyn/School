// Kalyn Howes
// 2.25.21
// Lab 4
// Tests all aspects of priority queues - used with HeapQ class

#include <iostream>
#include "HeapQ.h"
using namespace std;    

int main() {

    // testing w integers
    cout << "\n---- Integers -----\n" << endl;

    int size = 5;
    int defaultvalue = 0;
    HeapQ<int> heapQInts(size, true, defaultvalue);

    //heapQInts.OtherPrint();
    cout << heapQInts << endl;

    // other function testing...
    cout << "ExtractMax: " << heapQInts.ExtractMax() << endl;
    cout << "Peek: " << heapQInts.Peek() << endl;

    // --- STRINGS --- demonstrate with a set of people, represented by only their name
    cout << "\n\n---- Strings -----\n" << endl;
    int n = 0;
    cout << "Enter number of names: ";
    cin >> n;

    // create Heap with correct number of names
    // false because we dont want filled with randoms
    HeapQ<string> heapQNames(n, false, "NA"); 
    
    std::cout << heapQNames << std::endl;
    // fill heap with names:
    string s = "";
    for (int i = 0; i < n; i++) {
        cout << "Enter first name: ";
        std::cin >> s;
        heapQNames.Insert(s, i);
    }

    std::cout << heapQNames << std::endl;
    //heapQNames.OtherPrint();

    // other function testing...
    cout << "ExtractMax: " << heapQNames.ExtractMax() << endl;
    cout << "Peek: " << heapQNames.Peek() << endl;

    return 0;
}

