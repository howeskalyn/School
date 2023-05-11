/* Kalyn Howes
 * 4.11.21
 * Project 2
 * Spell-checking program.
 * The program will read a dictionary file and store it into a hash table. 
 * The user types in some text & the program report any misspelled words, and possible corrections.
 */

#include "Dictionary.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <algorithm> // transform
#include <cctype> // puncuation
#include <cstdlib> // timing
#include <ctime> // timing
#include <chrono> // timing
#include <fstream> // file work
#include <sstream> // string stream


// colored output
#define RESET "\033[0m"
#define RED "\033[31m"

using namespace std;

void hashStats(Dictionary);
void printDivider();

int main(int argc, char *argv[]) {

    // ---------- FILE/DATA LOADING ----------
    // open file: ex.) must pass in './Project2.exe' & 'english.txt'
    if (argc != 2) {
        cerr << "\nMust pass in 2 args." << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]); // opens file name given in command line

    // check for file open errors
    if (! inputFile) {
      cerr << "\nThere was an error opening the file." << endl;
      return -1;
    } else {
        cout << "\nWelcome to Spell Checker!" << endl;
        printDivider();
        cout << "The database has loaded..." << endl;
        printDivider();
    }
    
    // insert every word in to the hash table:
    int size = 1000; // holds size of the array of LLs
    Dictionary D(size); // create dictionary

    auto start = std::chrono::system_clock::now(); // start timer

    // fill array w insert function
    while (inputFile) {
        string str = "";
        inputFile >> str;
        transform(str.begin(), str.end(), str.begin(), ::toupper); // change input to all upper case
        D.insert(str);
    }

    auto end = chrono::system_clock::now(); // end timer
    chrono::duration<double> elapsed_seconds = end - start;
    hashStats(D); // shows statistics of dictionary hash table
    cout << "Total time taken to insert: " << elapsed_seconds.count() << " sec"<< endl;


    // ---------- USER INPUT ----------
    printDivider();
    cout << "Please enter some text: ";
    string userStr = "";
    getline(cin, userStr); // gets entire line, not just 1 word
    transform(userStr.begin(), userStr.end(), userStr.begin(), ::toupper); // change input to all upper case
    printDivider();

    // ignore puncutation & special characters
    int len = userStr.size();
    for (int i = 0; i < len; i++) {
        if (ispunct(userStr[i])) {
            userStr.erase(i--, 1);
            len = userStr.size();
        }
    }

    LinkedList *misspelled = new LinkedList; // holds misspelled words
    // goes through each word & searches for it
    istringstream iss(userStr);
    string word = "";
    cout << "You have entered the following words. The words highlighted red are misspelled.\n" << endl;
    while(iss >> word) {

        if (! D.search(word)) {// the word is NOT found add it to misspelled words list
            misspelled->putFront(word);
            cout << RED << word << endl;
        } else 
            cout << RESET << word << endl;
        cout << RESET;
    }

    cout << endl;
    printDivider();
    misspelled->printAsk(D); // asks user if they would like to add the misspelled words to the Dictionary

    start = std::chrono::system_clock::now(); // start timer again

    int totalsugs = misspelled->edits(D);  // go through each word in 'misspelled' & find the edit distance

    end = chrono::system_clock::now(); // end timer
    chrono::duration<double> elapsed_seconds2 = end - start;

    // report statistics about the text: 
    cout << endl;
    printDivider();
    cout << "\n*SUMMARY*" << endl;
    printDivider();
    cout << "Total misspelled words: " << misspelled->getSize() << endl;
    cout << "Total number of suggestions found: " << totalsugs << endl;
    cout << "Time required to find suggestions: " << elapsed_seconds2.count() << " sec" << endl;

    return 0;
}

// ---------- FUNCTIONS ----------

// prints statistics about the given hash table (dictionary)
void hashStats(Dictionary D) {
    cout << "Total words: " << D.totalItems() << endl;
    cout << "Biggest bin size: " << D.biggestBin() << endl;
    cout << "Smallest bin size: " << D.smallestBin() << endl;
    cout << "Total number of bins: " << D.totalBins() << endl;
    cout << "Number of used bins: " << D.usedBins() << endl;
    cout << "Average number of nodes in each bin: " << D.loadFactor() << endl;
}

// prints a divider for display organization purposes
void printDivider() {
    cout << "-------------------------------------------------------------" << endl;
}




