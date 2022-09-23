/* Kalyn Howes
 * 4.11.21
 * Project 2
 * Linked List - implementation file
*/

#include "Dictionary.h"
#include "LinkedList.h"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

// colored output
#define RESET "\033[0m"
#define RED "\033[31m"

// Constructor - allocate a LinkedList object with list set to NULL
LinkedList::LinkedList() {
	head = NULL;
}

// Destructor - delete all existing nodes in the List.
LinkedList::~LinkedList() {

	if (head) {
		ListNode *temp;
		ListNode *behindtemp;
		// while the head's next is not NULL
		while (head->next) {
			temp = head;
			// get to the end of the list
			while (temp->next) {
				behindtemp = temp;
				temp = temp->next;
			}
			delete temp;
			temp = NULL;
			behindtemp->next = NULL;
		}
		delete head;
		head = NULL;
	}
}

// deletes the node from the LL
void LinkedList::deleteNode(ListNode *n) {
    ListNode* temp;
    temp = n->next;
    n->next = temp->next;
    delete temp;
}

// inserts a new element to the front of the LL
void LinkedList::putFrontNOCHECK(std::string s) {

    ListNode *n = new ListNode();
    n->next = head;
    n->word = s;

    head = n;
}

// inserts a new element to the front of the LL only if it is not already in
void LinkedList::putFront(std::string s) {

	// only putFront if the word is not already in the LL
	if (!searchLocation(s)) {
		// insert at front
    	ListNode *n = new ListNode();
    	n->next = head;
    	n->word = s;

    	head = n;
	}
}

// returns the number of nodes in the LinkedList
int LinkedList::getSize() {
    int size = 0;
    ListNode *temp = head;

    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    
    return size;
}

// returns true if the word was found & false otherwise
bool LinkedList::searchLocation(std::string str) {
	ListNode *temp = head;
	bool ret = false;
	while (temp) {
		if (temp->word.compare(str) == 0) { // better than using ==
			ret = true;
			break;
		} else
			temp = temp->next;
	}
	return ret;
}

// check is the LL is empty
// returns true if it is empty & false if not
bool LinkedList::isEmpty() {
	bool ret = false;

	if (head == NULL)
		ret = true;

	return ret;
}

// prints the words of the LL in list form
void LinkedList::printList() {
    //std::cout << "Printing list:" << std::endl;
	ListNode *temp = head;

	while (temp) {
		std::cout << temp->word << std::endl;
		temp = temp->next;
	}
}

// prints the words of the LL side-by-side
void LinkedList::print() {
    //std::cout << "Printing list:" << std::endl;
	ListNode *temp = head;

	while (temp) {
		std::cout << temp->word << " ";
		temp = temp->next;
	}
}

void LinkedList::printAsk(Dictionary D) {
	ListNode *temp = head;
	std::string answer = "";

	while (temp) {
		std::cout << "Would you like to add the word, " << RED << temp->word << RESET << ", to the Dictionary? ";
		std::cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::toupper); // change input to all upper case

		if ( (answer.compare("YES") == 0)|| (answer.compare("Y") == 0) ) {
			D.insert(temp->word);
			std::cout << "Your word was added to the Dictionary." << std::endl;
		} else
			std::cout << "Your word was NOT added to the Dictionary." << std::endl;

		temp = temp->next;
	}

}

// ------------------------------------------------------------------------------------------------------------------------
// ------------ EDIT DISTANCE FUNCTIONS ------------

// goes through the given LL of words and finds every possible string with 1 character replaced from the current word
// only returns words found from this process that are in the given Dictionary
LinkedList* LinkedList::editReplace(Dictionary D, std::string word) {

	LinkedList *list = new LinkedList;
	std::string tempword = word;

	for (int i = 0; i < word.length(); i++) {
			std::string tempword = word;

			// go through ASCII - change current index to each letter of alphabet & save it
			for (int ascii = 65; ascii < 91; ascii++) {
				tempword[i] = ascii;

				// check if possible word is in Dictionary - if it is, save it & print it out
				if (D.search(tempword))
					list->putFront(tempword);
			}
		}

	return list;
}

// goes through the given LL of words and finds every possible string with 1 character added to the current word
// only returns words found from this process that are in the given Dictionary
LinkedList* LinkedList::editAdd(Dictionary D, std::string word) {
	LinkedList *list = new LinkedList; 

		for (int i = 0; i < word.length(); i++) {
			std::string tempword = word;

			// go through ASCII - change current index to each letter of alphabet & save it
			for (int ascii = 65; ascii < 91; ascii++) {
				tempword = word;
				char asciichar = ascii; // holds ascii letter
				std::string asciiword(1, asciichar); // converts letter to a string for substr

				// if adding in front of the word, just concat it
				if (i == 0) 
					tempword = asciiword + tempword;
				// if adding at the end, just concat
				else if (i == word.length() - 1)
					tempword += asciiword;
				else 
					tempword.insert(i, asciiword);

				// check if possible word is in Dictionary - if it is, print it out
				if (D.search(tempword))
					list->putFront(tempword);
			}
		}
	
	return list;
}

// goes through the given LL of words and finds every possible string with 1 character removed from the current word
// only returns words found from this process that are in the given Dictionary
LinkedList* LinkedList::editRemove(Dictionary D, std::string word) {
	LinkedList *list = new LinkedList; // holds all words within 1 character removed from the input

	for (int i = 0; i < word.length(); i++) {
		std::string tempword = word;
		tempword = (tempword.substr(0,i) + tempword.substr(i+1, word.length()));

		// if the word is in the dictionary, add it to return list
		if (D.search(tempword))
			list->putFront(tempword);
	}

	return list;
}

// finds every possible string with 2 adjacent characters swapped from the given word
// only returns words found from this process that are in the given Dictionary
LinkedList* LinkedList::editSwap(Dictionary D, std::string word) {
	LinkedList *list = new LinkedList;

	for (int i = 0; i < word.length(); i++) {
		std::string tempword = word;
			
		// swap current index, i, with index i + 1
		char t = tempword[i];
		tempword[i] = tempword[i+1];
		tempword[i+1] = t;
		
		// if the word is in the dictionary, add it to return list
		if (D.search(tempword))
			list->putFront(tempword);
	}

	return list;
}

int LinkedList::edits(Dictionary D) {	
	LinkedList *replaces = new LinkedList;
	LinkedList *adds = new LinkedList;
	LinkedList *removes = new LinkedList;
	LinkedList *swaps = new LinkedList;
	LinkedList *total = new LinkedList;	
	int suggestions = 0; // keeps track of number of suggestions

	// go through LL of misspelled words
	ListNode *temp = head;
	while (temp) {

		std::string word = temp->word;

		replaces = editReplace(D, word);
		adds = editAdd(D, word);
		removes = editRemove(D, word);
		swaps = editSwap(D, word);

		// add words from all 4 LL together into one & print it
		total = replaces->addLLs(adds, removes, swaps);
		suggestions = total->getSize();

    	// cout << "\n\nWITHOUT DUPS: " << endl;
    	// total = total->removeDups();

		if (total->isEmpty()) {
			std::cout << "\n-------------------------------------------------------------" << std::endl;
			std::cout << "There are no suggestions available for " << word << "." << std::endl;
		} else {
			std::cout << "\n-------------------------------------------------------------" << std::endl;
			std::cout << "Below are the words within one edit distance of " << word << ". " << std::endl;
			std::cout << "\nSuggestions for " << RED << word << RESET << ": \n" << std::endl;
			total->print();
			std::cout << std::endl;

			// find words that are within one edit distance of the one-edit-distance suggestions:
			// go through 'total' LL with similar process
			LinkedList *total2 = new LinkedList;
			LinkedList *replaces2 = new LinkedList;
			LinkedList *adds2 = new LinkedList;
			LinkedList *removes2 = new LinkedList;
			LinkedList *swaps2 = new LinkedList;

			ListNode *temp2 = total->head;
			std::cout << "\n-------------------------------------------------------------" << std::endl;
			std::cout << "Below are the words within two edit distances of " << word << ". " << std::endl;
			while(temp2) {

				std::string word2 = temp2->word;

				replaces2 = editReplace(D, word2);
				adds2 = editAdd(D, word2);
				removes2 = editRemove(D, word2);
				swaps2 = editSwap(D, word2);

				// add words from all 4 LL together into one & print it
				total2 = replaces2->addLLs(adds2, removes2, swaps2);
				suggestions += total2->getSize();

				std::cout << "\nSuggestions for " << RED << word2 << RESET << ": \n" << std::endl;
				total2->print();
				std::cout << std::endl;

				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
	return suggestions;
}

// go through each of the three input LL(& the LL it was called on) and add them
// to a new LL to return
LinkedList* LinkedList::addLLs(LinkedList* B, LinkedList* C, LinkedList* D) {
    LinkedList *total = new LinkedList;

    // go through first LL:
	ListNode *temp = head; // LL the function was called on
	while (temp) {
		total->putFront(temp->word);
		temp = temp->next;
	}

	// go through second LL:
	temp = B->head; 
	while (temp) {
		total->putFront(temp->word);
		temp = temp->next;
	}

	// go through third LL:
	temp = C->head; // LL the function was called on
	while (temp) {
		total->putFront(temp->word);
		temp = temp->next;
	}

	// go through fourth LL:
	temp = D->head; // LL the function was called on
	while (temp) {
		total->putFront(temp->word);
		temp = temp->next;
	}

	return total;
}