/*
 * TNode.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: Kalyn Howes
 */

#include "TNode.h"
#include <iostream>

// Constructor - initiates all pointers to NULL
TNode::TNode() {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	data = 0;
}

// Prints node information
void TNode::printNode() {
	std::cout << "Parent: " << parent << " Left: " << left << " Right: " << right << " Data: " << data << std::endl;
}

