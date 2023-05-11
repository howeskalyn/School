// Kalyn Howes
// 4.1.21
// Lab8 - Binary Search Trees
// Test program that demonstrates the correctness of the BST methods, displaying the tree after modifications. 

#include "BinaryTree.h"
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

    // PART ONE - TESTING:
    int rootkey = 2;
    BinaryTree T(rootkey); // creates tree with root equal to rootkey
    cout << "Root print: " << endl;
    T.printInOrder(T.getRoot());

    // hardcode values
    T.insert(4);
    T.insert(10);
    T.insert(13);
    T.insert(7);
    T.insert(21);
    cout << "\nReprint w/ newly inserted nodes: " << endl;
    T.printInOrder(T.getRoot());

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
    int u = 10;
    cout << "Successor of " << u << ": " << T.successorMain(u)->key << endl;

    // inorder test:
    cout << "\nInorder Call: " << endl;
    T.inorder(T.getRoot());

    // remove test:
    int d = 7;
    cout << "\nRemoving: " << d << endl;
    T.removeMain(T, d);
    cout << "Reprint:" << endl;
    T.printInOrder(T.getRoot());
    

    // PART TWO - TIMING
    cout << "\n\nPart 2: Timing" << endl;
    // time how long it takes to insert, find, delete 1000, 2000, 3000, etc.
    ofstream outputFile;
    outputFile.open("timing.txt");

    int n = rand() % 10 + 1; // finds random # between 1 and 10 to be the root
    BinaryTree T2(n);
    int size = 500; // number of elements in the tree

    // ----- 1) INSERT -----
    outputFile << "\n----- INSERT -----" << endl;
    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::system_clock::now();
    
        // random fill:
        int random = 0;
        for (int i = 0; i < size; i++) {
            random = rand() % 100 + 1;
            T2.insert(random);
        }
        //T2.printInOrder(T2.getRoot()); // print testing

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "Inserting " << size << " elements took: " << elapsed_seconds.count() << endl;
        size += 500;
    }

    // ----- 2) SEARCH -----
    outputFile << "\n----- SEARCH -----" << endl;
    size = 500;
    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::system_clock::now();
    
        int random = 0;
        random = rand() % 100 + 1;
        T2.search(random); // searches for random number
    
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "For size: " << size << ", searching for key " << random << " took: " << elapsed_seconds.count() << endl;
        //T2.printInOrder(T2.getRoot()); // print testing
        size += 500;
    }

    // ----- 3) REMOVE -----
    outputFile << "\n----- REMOVE -----" << endl;
    size = 500;
    // loop through using different sizes
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::system_clock::now();
    
        int random = 0;
        random = rand() % 100 + 1;
        T2.removeMain(T2, random); // chooses a random number between 1 & 100 to remove

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        outputFile << "For size: " << size << ", removing key " << random << " took: " << elapsed_seconds.count() << endl;
        size += 500;
    }
	
    outputFile.close();
    
    return 0;
}