//==========================================================================================
// Name        : Decrypt.cpp
// Author      : Kalyn Howes
// Date        : 11.25.2020
// Description : Opens an encrypted file and displays its decrypted contents on the screen.
//==========================================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

void decryption(map<char, char>&, string&, string&);

int main() {

	/*
	 * MAP SET UP (opposite from encryption):
	 */
	map<char, char> codes;
	char letter = 0;

	// symbols for uppercase
	char symbol = 33;
	for (int i = 65; i < 91; i++) {
		letter = i;
		codes.insert(pair<char, char>(symbol, letter));
		symbol++;
	}

	/* print the map for testing
	 for (auto &t : codes)
	 cout << t.first << " " << t.second << "\n";
	 */


	/*
	 * FILE SET UP:
	 */
	string inputname = "";

	cout << "Input the input filename: ";
	cin >> inputname;

	// open input file
	ifstream inputFile;
	inputFile.open(inputname);

	// Shows an error message if the file doesnt open
	if (!inputFile) {
		cerr << "Error opening input file." << endl;
		return -1;
	} else
		cout << "Input file opened." << endl;

	// store every string in the input file
	vector<string> ifile;
	string word = "";
	while (inputFile >> word) {
		ifile.push_back(word);
	}

	/* print vector contents for testing:
	for (int i = 0; i < ifile.size(); i++)
		cout << ifile[i] << endl;
		*/

	/*
	 * DECRYPTION TO CONSOLE:
	 */
	// fills decoded vector with blanks for now
	vector<string> decoded;
	for (int i = 0; i < ifile.size(); i++)
		decoded.push_back("");

	// goes through every string in the file by using the created vector
	for (int i = 0; i < ifile.size(); i++)
		decryption(codes, ifile[i], decoded[i]);

	// send coded version to console
	for (int i = 0; i < decoded.size(); i++)
		cout << decoded[i] << " ";

	return 0;
}

// Decrypts a given string
// Parameters: mapping, string to be decrypted, decrypted version of the string (by reference)
void decryption(map<char, char> &codes, string &coded, string &decoded) {

	for (int i = 0; i < coded.size(); i++) {
		map<char, char>::iterator it = codes.find(coded[i]);
		decoded.insert(i, 1, it->second);
	}
}

