/*
 * TNode.h
 *
 *  Created on: Nov 2, 2020
 *      Author: Kalyn Howes
 */

#ifndef TNODE_H_
#define TNODE_H_

class TNode {
	friend class BST;

private:
	TNode *parent; // not needed?
	TNode *left;
	TNode *right;
	int data;

public:
	TNode();
	void printNode();
};

#endif /* TNODE_H_ */

