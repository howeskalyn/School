//============================================================================
// Name        : Encrypt.cpp
// Author      : Kalyn Howes
// Date        : 11.25.2020
// Description : Uses a map to assign "codes" to each letter of the alphabet
//               to encrypt a file's contents to a new file.
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

string removeSpecials(string);
void encryption(map<char, char>&, string&, string&);

int main() {

	/*
	 * MAP SET UP:
	 */
	map<char, char> codes;
	// symbols for uppercase
	char letter = 65;
	for (int i = 33; i < 59; i++) {
		char temp = i;
		codes.insert(pair<char, char>(letter, temp));
		letter++;
	}

	/* print the map for testing
	 for (auto &t : codes)
	 cout << t.first << " " << t.second << "\n";
	*/

	/*
	 * FILE SET UP:
	 */
	string inputname = "", outputname = "";

	cout << "Input the input filename: ";
	cin >> inputname;
	cout << "Input the output filename: ";
	cin >> outputname;

	// open input and output files
	ifstream inputFile;
	inputFile.open(inputname);
	ofstream outputFile;
	outputFile.open(outputname);

	// Shows an error message if the files dont open.
	if (!inputFile) {
		cerr << "Error opening input file." << endl;
		return -1;
	} else
		cout << "Input file opened." << endl;
	if (!outputFile) {
		cerr << "Error opening output file." << endl;
		return -1;
	} else
		cout << "Output file opened." << endl;

	// store every string in the input file & remove special characters
	vector<string> ifile;
	string word = "";
	while (inputFile >> word) {
		transform(word.begin(), word.end(), word.begin(), ::toupper); // Make all letters uppercase
		word = removeSpecials(word); // Remove any special characters from the words
		ifile.push_back(word);
	}

	/* print vector contents for testing:
	 for (int i = 0; i < ifile.size(); i++)
	 cout << ifile[i] << endl;
	 */

	/*
	 * ENCRYPTION TO OUTPUT FILE:
	 */
	// fills coded vector with blanks for now
	vector<string> coded;
	for (int i = 0; i < ifile.size(); i++)
		coded.push_back("");

	// goes through every string in the file by using the created vector
	for (int i = 0; i < ifile.size(); i++)
		encryption(codes, ifile[i], coded[i]);

	// send coded version to outputfile
	for (int i = 0; i < coded.size(); i++)
		outputFile << coded[i] << " ";

	// close all used files
	inputFile.close();
	outputFile.close();

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

// Encrypts a given string
// Parameters: mapping, string to be encrypted, encrypted version of the string (by reference)
void encryption(map<char, char> &codes, string &message, string &coded) {

	for (int i = 0; i < message.size(); i++) {
		map<char, char>::iterator it = codes.find(message[i]);
		coded.insert(i, 1, it->second);
	}
}
