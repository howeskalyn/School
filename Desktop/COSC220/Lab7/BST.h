/*
 * BST.h
 *
 *  Created on: Nov 2, 2020
 *      Author: Kalyn Howes
 */

#ifndef BST_H_
#define BST_H_
#include "TNode.h"

class BST {
	friend class TNode;

private:
	TNode *root;

public:

	BST();
	~BST();
	void destroySubTree(TNode*);
	void inOrder(TNode*) const;
	void preOrder(TNode*) const;
	void postOrder(TNode*) const;
	void bstInsert(int);
	void insert(TNode*&, TNode*&);
	void bstDelete(int);
	void deleteNode(int, TNode*&);
	bool bstSearch(int);

	TNode* GetRoot() { return root; }
};

#endif /* BST_H_ */
