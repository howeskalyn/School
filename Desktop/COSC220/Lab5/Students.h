/*
 * Students.h
 *
 *  Created on: Oct 20, 2020
 *      Author: kalynhowes
 */

#ifndef STUDENTS_H_
#define STUDENTS_H_
#include <iostream>
using namespace std;

// definition of the Struct Type Students
struct Students {
	char lastName[20];   // student lastname
	char firstName[20];  // student's firstname
	int idNumber;        // student ID

	Students();         // constructor
	void printStudent(); // print a student information
};

#endif

