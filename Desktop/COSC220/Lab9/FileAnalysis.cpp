//=========================================================================================
// Name        : FileAnalysis.cpp
// Author      : Kalyn Howes
// Date        : 11.25.2020
// Description : Reads the contents of two text files and compares them in five ways.
//==========================================================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string removeSpecials(string);
vector<string> unique(vector<string>);
vector<string> notBoth(vector<string>, vector<string>);
int search(vector<string>, string);

int main() {

	string filename1 = "", filename2 = "", word = "";
	vector<string> file1, file2;

	cout << "Input the input first filename: ";
	cin >> filename1;
	cout << "Input the input second filename: ";
	cin >> filename2;

	ifstream inputFile1, inputFile2;
	inputFile1.open(filename1);
	inputFile2.open(filename2);

	// Shows an error message if file 1 doesn't open.
	if (!inputFile1) {
		cerr << "\nError opening file 1." << endl;
		return -1;
	} else
		cout << "\nFile 1 opened." << endl;
	// Shows an error message if file 2 doesn't open.
	if (!inputFile2) {
		cerr << "\nError opening file 2." << endl;
		return -1;
	} else
		cout << "\nFile 2 opened." << endl;

	// store every word in file 1
	while (inputFile1 >> word) {
		word = removeSpecials(word);
		file1.push_back(word);
	}
	// store every word in file 2
	while (inputFile2 >> word) {
		word = removeSpecials(word);
		file2.push_back(word);
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * 1.)
	 * displays unique words in each file
	 */
	cout << "\n1.) UNIQUE WORDS IN EACH FILE." << endl;

	vector<string> uniques1 = unique(file1); // create vector to hold unique words for file 1
	vector<string> uniques2 = unique(file2); // create vector to hold unique words for file 2

	// print unique words for file 1
	cout << "1a.) UNIQUE WORDS IN FILE 1." << endl;
	for (int i = 0; i < uniques1.size(); i++)
		cout << uniques1[i] << endl;

	// print unique words for file 2
	cout << "1b.) UNIQUE WORDS IN FILE 2." << endl;
	for (int i = 0; i < uniques2.size(); i++)
		cout << uniques2[i] << endl;

	/* ------------------------------------------------------------------------------------------------------------------
	 * 2.)
	 * displays list of the words that appear in both files
	 */
	cout << "\n2.) ALL WORDS IN BOTH FILES." << endl;
	// file 1
	cout << "2a.) WORDS IN FILE 1." << endl;
	for (int i = 0; i < file1.size(); i++)
		cout << file1[i] << endl;
	// file 2
	cout << "2b.) WORDS IN FILE 2." << endl;
	for (int i = 0; i < file2.size(); i++)
		cout << file2[i] << endl;

	/* ------------------------------------------------------------------------------------------------------------------
	 * 3.)
	 * displays a list of the words that appears in the first file, but not the words also in the second
	 */
	cout << "\n3.) ALL WORDS IN FIRST FILE BUT NOT IN SECOND." << endl;
	for (int i = 0; i < file1.size(); i++) {
		if (search(file2, file1[i]) < 0)
			cout << file1[i] << endl;
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * 4.)
	 * displays a list of the words that appears in the second file, but not the words also in the first
	 */
	cout << "\n4.) ALL WORDS IN SECOND FILE BUT NOT IN FIRST." << endl;
	for (int i = 0; i < file2.size(); i++) {
		if (search(file1, file2[i]) < 0)
			cout << file2[i] << endl;
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * 5.)
	 * displays a list of all the words that appears in either the first or second file, but not in both.
	 */
	vector<string> diffs = notBoth(file1, file2);
	cout << "\n5.) WORDS IN EITHER THE FIRST OR SECOND FILE, BUT NOT BOTH."
			<< endl;
	for (int i = 0; i < diffs.size(); i++)
		cout << diffs[i] << endl;

	// close all used files
	inputFile1.close();
	inputFile2.close();

	return 0;
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

// finds all the words that appear in either the first or second file, but not in both
vector<string> notBoth(vector<string> file1, vector<string> file2) {
	vector<string> sames;
	for (int i = 0; i < file1.size(); i++) { 	// go through file  1
		for (int j = 0; j < file2.size(); j++) {	// go through file  2
			if (file1[i] == file2[j]) { // if two words are the same add to sames vector
				sames.push_back(file1[i]);
			}
		}
	}

	/* testing - print sames
	 cout << "TESTING SAMES: " << endl;
	 for (int i = 0; i < sames.size(); i++) {
	 cout << sames[i] << endl;
	 } */

	vector<string> diffs; // file1 - sames & file2 - sames
	// if the word in file 1 is NOT in sames, it is added to the diffs
	for (int i = 0; i < file1.size(); i++) {
		if (search(sames, file1[i]) < 0)
			diffs.push_back(file1[i]);
	}

	// if the word in file 2 is NOT in sames, it is added to the diffs
	for (int i = 0; i < file2.size(); i++) {
		if (search(sames, file2[i]) < 0)
			diffs.push_back(file2[i]);
	}

	return diffs;
}

// linear search for strings in a vector
int search(vector<string> vec, string x) {
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].compare(x) == 0)
			return i;
	return -1;
}

