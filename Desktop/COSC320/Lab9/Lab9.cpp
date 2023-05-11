// Kalyn Howes
// 4.15.21
// Lab 9 - Red-Black Trees
// Test program that demonstrates the correctness of the RBT methods, displaying the tree after modifications. 

#include "RBTree.h"
#include <iostream>
#include <cstdlib> // timing
#include <ctime> // timing
#include <chrono> // timing
#include <fstream> // files
#include <stdlib.h> // rand
#include <time.h> // reset for rand

using namespace std;

int main() {
    srand(time(NULL));

    // PART ONE - FUNCTION TESTING:
    int rootkey = 2;
    RBTree T(rootkey); // creates tree with root equal to rootkey
    cout << "Root print: " << endl;
    T.printInOrder(T.getRoot());
    cout << endl;

    // hardcode values
    T.insert(4, true);
    T.insert(10, true);
    T.insert(7, true);
    T.printInOrder(T.getRoot()); 
    T.insert(3, true);
    
    cout << "Reprint (inorder):" << endl;
    T.printInOrder(T.getRoot()); // something like T.print() would be more user friendly...
    cout << "\nReprint (preorder):" << endl;
    T.printPreOrder(T.getRoot());

    // search test:
    int s = 3;
    cout << "\nSearch for " << s << "." << endl;
    bool ret = T.search(s);
    if (ret)
        cout << "Was it found? Yes." << endl;
    else
         cout << "Was it found? NO." << endl;

    // max, min, & successor test:
    cout << "\nMinimum: " << T.minimum(T.getRoot())->key << endl;
    cout << "Maximum: " << T.maximum(T.getRoot())->key << endl;
    int u = 4;
    cout << "Successor of " << u << ": " << T.successorMain(u)->key << endl;

    // inorder test:
    cout << "\nInorder Call: " << endl;
    T.inorder(T.getRoot());

    // remove test:
    int d = 7;
    cout << "\nRemoving: " << d << endl;
    T.removeMain(d);
    cout << "Reprint (inorder):" << endl;
    T.printInOrder(T.getRoot());
    cout << "\nReprint (preorder):" << endl;
    T.printPreOrder(T.getRoot());

    // PART TWO - TIMING
    cout << "\n\n---- Part 2: Timing ----" << endl;

    int n = rand() % 10 + 1; // finds random # between 1 and 10 to be the root
    cout << "Root: " << n << endl;
    int size = 500000; // number of elements in the tree

    // time how long it takes to insert, find, delete 1000, 2000, 3000, etc.
    ofstream outputFile;
    outputFile.open("timing.txt");

    if (outputFile)
        cout << "File is open." << endl;
    else
        cout << "Error opening file";

    // ----- 1) INSERT -----
    outputFile << "\n----- INSERT -----" << endl;
    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        RBTree T2(n); // create tree w random root from above

        auto start = std::chrono::system_clock::now();
    
        // random fill:
        int random = 0;
        for (int i = 0; i < size; i++) {
            random = rand() % 100 + 1;
            
            T2.insert(random, false);
        }
        //T2.printInOrder(T2.getRoot()); // print testing

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "Inserting " << size << " elements took: " << elapsed_seconds.count() << endl;
        size += 10000;
    }

    // ----- 2) SEARCH -----
    outputFile << "\n----- SEARCH -----" << endl;
    size = 500000;
    RBTree T3( rand() % 10 + 1); // create tree w random root
    // random fill:
    int random = 0;
    for (int i = 0; i < size; i++) {
        random = rand() % 100 + 1;
        T3.insert(random, false);
    }

    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::system_clock::now();
    
        int random = 0;
        random = rand() % 100 + 1;
        T3.search(random); // searches for random number
    
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "For size: " << size << ", searching for key " << random << " took: " << elapsed_seconds.count() << endl;
        //T3.printInOrder(T3.getRoot()); // print testing
        size += 10000;
    }

    // ----- 3) REMOVE -----
    outputFile << "\n----- REMOVE -----" << endl;
    size = 500000;
    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::system_clock::now();
    
        int random = 0;
        random = rand() % 100 + 1;
        T3.removeMain(random); // chooses a random number between 1 & 100 to remove

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "For size: " << size << ", removing key " << random << " took: " << elapsed_seconds.count() << endl;
        size += 10000;
    }
	
    outputFile.close();
    cout << "File is closed. Program ending..." << endl;

    return 0;
}