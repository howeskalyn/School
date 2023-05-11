/* Kalyn Howes
 * 4.11.21
 * Project 2
 * Dictionary Class - implementation file:
 *  contains a hash table structure, with an array of pointers, to a chain 
 *  (doubly-linked list) of values and keys that each map to that cell of 
 *  the array under the chosen hash function
*/

#include "Dictionary.h"
#include "LinkedList.h"
#include <iostream>
#include <cstring>
#include <math.h>

// constructor - takes in size of the array (of Linked Lists)
Dictionary::Dictionary(int s) {
  // allocate the new linked lists
  // (check) calls LinkedList() for each element of array
  size = s;
  T = new LinkedList[s];
}

// destructor
Dictionary::~Dictionary() {
  //delete T;
}

void Dictionary::insert(std::string word) {
  // convert string to char* for strTo128 function:
  int n = word.length();
  char charArr[n + 1];
  strcpy(charArr, word.c_str()); // copying the contents of the string to char array

  T[hash(strTo128(charArr))].putFrontNOCHECK(word); // this seems wrong ???
}

// uses the “multiplication method” to compute the hash
size_t Dictionary::hash(size_t k) {
  size_t ret = 0; // holds return

  // maintain three hard-coded internal variables:
  size_t w = 32;
  size_t p = 7; // can change this to differ the hashing process
  double A = ( sqrt(5) - 1 ) / 2; // number given from class

  size_t one = 1; // get 1 as a size_t
  size_t s = A * size_t(one << w);
  size_t prod = k * s;

  // restrict k to be only w least sig, same as "masking" k with 1111..1
  // i.e. w 1's in a row which is 2^w - 1
  size_t mask = (one << w) - one;

  // all non-zeros after w least sig will now be 0.
  size_t masked_k = prod & mask;

  // get rid of the rightmost (w - p)
  ret = masked_k >> (w - p);

  return ret;
}

// takes each character as an ASCII value & interprets the string as a number in base-128
// (because ASCII characters have numerical value 0-127)
size_t Dictionary::strTo128(char* str) {
    size_t sum = 0; // return value

    int n = strlen(str);
    for(int i = 0; i < n; i++){
        // str[i] * 128^(n-1) = str[i] * 2^(7*(n-1)) = str[i] << 7*(n-1)
        // make sure we convert to avoid prematurely overflowing
        sum += size_t(str[i]) << 7 * (n - i - 1);
    }

    return sum;
}

// returns the total number of items in the hash table
// found by traversing through the array of linked lists & summing up each item
int Dictionary::totalItems() {
    int total = 0;

    // go through array
    for (int i = 0; i < size; i++) {
        // go through linked list
        total += T[i].getSize();
    }

    return total;
}

// returns the total number of bins in the hash table
// just equals the size of the array
int Dictionary::totalBins() {
    return size;
}

// returns the biggest bin size in the hash table
// goes through each bin & finds the one with the most Linked List nodes
int Dictionary::biggestBin() {
    int biggest = T[0].getSize(); // set biggest to first LL to begin

    // go through each bin (array)
    for (int i = 0; i < size; i++) {
      if (T[i].getSize() > biggest)
        biggest = T[i].getSize();
    }

    return biggest;
}

// returns the smallest bin size in the hash table
// goes through each bin & finds the one with the least Linked List nodes
int Dictionary::smallestBin() {
    int smallest = T[0].getSize(); // set smallest to first LL to begin

    // go through each bin (array)
    for (int i = 0; i < size; i++) {
      if (T[i].getSize() < smallest)
        smallest = T[i].getSize();
    }

    return smallest;
}

// returns number of used bins in the hash table
// goes through each bin & finds the ones with Linked List nodes (non-empty)
int Dictionary::usedBins() {
    int used = 0;

    // go through array
    for (int i = 0; i < size; i++) {

      // if the LL size is NOT 0, the bin is being used
      if (T[i].getSize() != 0)
        used++;
    }

    return used;
}

// returns average number of nodes in each bin in the hash table
// divides the total number of items by the total number of bins
double Dictionary::loadFactor() {
    return ( (double)totalItems() / (double)size ); // casting to ensure decimal average
}

// searches the hash table for a specific word
bool Dictionary::search(std::string str) {
  bool found = false; // holds return

  // go through array
  for (int i = 0; i < size; i++) {
    // go through LL
    if (T[i].searchLocation(str)) // if the str was found, found = true
      found = true;
  }

  return found;
}

/*
// returns a LL of strings that have a 1 character difference of the input word
LinkedList* Dictionary::search1char(char* word, int size) {
  LinkedList *rets = new LinkedList; // holds return words (within 1 character of input)

  // go through array
  for (int i = 0; i < size; i++) {
    // go through LL
    LinkedList::ListNode *temp = T->getHead();
    while (temp) {

      // change LL word to a char array:
      std::string t = temp->word;
      int LLsize = t.length() + 1;
      char LLword[LLsize];
      strcpy(LLword, t.c_str());

      // if the words arent the same length, there is already an issue
      if (size == LLsize) {
        int diffs = 0; // holds number of characters that are different

        // go through each character in the input word
        for (int i = 0; i < size; i++) {
          if (LLword[i] != word[i]) // if the character does not match, diffs increments
            diffs++;
        }

        // if the differences are only 1, add the Dictionary word to the return list
        if (diffs == 1)
          rets->putFront(temp->word);
      }

      temp = temp->next;

    } // end of LL loop (while)

  } // end of array loop (for)

  return rets;
}

// returns a LL of strings that have 1 character added to the input word 
LinkedList* Dictionary::search1add(char* word, int size) {
  LinkedList *rets = new LinkedList; // holds return words

  // go through array
  for (int i = 0; i < size; i++) {
    // go through LL
    LinkedList::ListNode *temp = T->getHead();
    while (temp) {

      // change LL word to a char array:
      std::string t = temp->word;
      int LLsize = t.length() + 1;
      char LLword[LLsize];
      strcpy(LLword, t.c_str());

      // input word should be one char more than the Dictionary word
      if (size == LLsize - 1) {


      }

    }

  }


  return rets;
}

// returns a LL of strings that have 2 adjacent characters swapped
LinkedList* Dictionary::searchSwapped(char* word, int size) {
  LinkedList *rets = new LinkedList; // holds return words

  // go through array
  for (int i = 0; i < size; i++) {
    // go through LL
    LinkedList::ListNode *temp = T->getHead();
    while (temp) {

      // change LL word to a char array:
      std::string t = temp->word;
      int LLsize = t.length() + 1;
      char LLword[LLsize];
      strcpy(LLword, t.c_str());

      // input word should be same size as Dictionary word
      if (size == LLsize) {


      }

    }

  }


  return rets;
} */


// prints array
void Dictionary::printArr() {
  for (int i = 0; i < size; i++)
    T[i].printList();
}
