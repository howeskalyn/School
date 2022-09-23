/*
 * Students.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: kalynhowes
 */

#include "Students.h"
#include <iostream>
using namespace std;

// constructor which initiate a student information
Students::Students() {
	idNumber = 0;

	cout << "Enter student's ID number: ";
	cin >> idNumber;

	cout << "Enter student's last name:";
	cin >> lastName;

	cout << "Enter student's last name:";
	cin >> firstName;
}

// print a student information with following format: ID# 1234 – Jackson, Michael
void Students::printStudent() {
	cout << "ID# " << idNumber << " - " << lastName << ", " << firstName
			<< endl;
}

