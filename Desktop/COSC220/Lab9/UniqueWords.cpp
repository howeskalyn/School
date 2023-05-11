//============================================================================
// Name        : UniqueWords.cpp
// Author      : Kalyn Howes
// Date        : 11.25.2020
// Description : Opens a specified text file & displays a list of all
//               the unique words found in the file.
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> unique(vector<string>);
int search(vector<string>, string);
string removeSpecials(string);

int main() {

	string filename = "", word = "";
	vector<string> words;

	cout << "Input the input filename: ";
	cin >> filename;

	ifstream inputFile;
	inputFile.open(filename);

	// Shows an error message if the file doesn't open.
	if (!inputFile) {
		cerr << "Error opening file." << endl;
		return -1;
	} else
		cout << "File opened." << endl;

	// store every word in file & removes special characters if any
	while (inputFile >> word) {
		word = removeSpecials(word);
		words.push_back(word);
	}

	// create vector to hold unique words
	vector<string> uniques = unique(words);

	// print unique words
	for (int i = 0; i < uniques.size(); i++)
		cout << uniques[i] << endl;

	// close files used
	inputFile.close();

	return 0;
}

//finds unique words in a vector
vector<string> unique(vector<string> words) {
	vector<string> uniques;

	// go through all of the words and add them to unique, if it is already added, do not
	for (int i = 0; i < words.size(); i++) {
		if (search(uniques, words[i]) < 0)
			uniques.push_back(words[i]);
	}
	return uniques;
}

// Remove special characters from file.
string removeSpecials(string s) {
	for (int i = 0; i < s.size(); i++) {
		if ((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z')) {
			s.erase(i, 1);
			i--;
		}
	}
	return s;
}

// linear search for strings in a vector
int search(vector<string> vec, string x) {
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].compare(x) == 0)
			return i;
	return -1;
}
