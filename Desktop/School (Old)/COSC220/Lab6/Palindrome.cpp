//============================================================================
// Name        : Palindrome2.cpp
// Description : Has a bool function that uses recursion to determine if a
//		 		 string argument is a palindrome. The function returns true if
//				 the argument read the same forward and backward.
//				 Demonstrates the function in a program.
// Author      : Kalyn Howes
// Date		   : 11/3/20
//============================================================================
#include <iostream>
using namespace std;

bool palindrome(string, int, int);

int main() {
	string s = "";

	cout << "Enter a string, no spaces and all lower case: ";
	cin >> s;

	// If it is a palindrome, the user is told.
	if (palindrome(s, 0, s.size() - 1))
		cout << s << " is a palindrome.";
	// If not, the user is told.
	else
		cout << s << " is not a palindrome.";

	return 0;
}

// Determines if a string is a palindrome using recursion.
// Returns true if it is a palindrome and false otherwise.
bool palindrome(string s, int start, int end) {
	bool ret = true;

	// If the letter at the beginning and end are different, it is not a palindrome.
	if (s[start] != s[end])
		ret = false;
	// The word must be longer than 1 letter.
	else if (start != end)
		ret = palindrome(s, start + 1, end - 1);

	return ret;
}

