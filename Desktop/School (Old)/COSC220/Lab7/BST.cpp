/*
 * BST.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: Kalyn Howes
 */

#include "BST.h"
#include "TNode.h"
#include <iostream>
#include <stack>
using namespace std;

// Constructor – initiates root as NULL
BST::BST() {
	root = nullptr;
}

// Destructor – cleans all nodes in the Binary Search Tree
BST::~BST() {
	destroySubTree(root);
}

// Called by destructor - deleted a subtree
void BST::destroySubTree(TNode *nodePtr) {

	if (nodePtr) {

		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}

}

// inOrder - displays tree inorder
void BST::inOrder(TNode *nodePtr) const {

	if (nodePtr) {
		inOrder(nodePtr->left);
		cout << nodePtr->data << endl;
		inOrder(nodePtr->right);
	}
}

// preOrder - displays tree in preorder
void BST::preOrder(TNode *nodePtr) const {

	if (nodePtr) {
		cout << nodePtr->data << endl;
		preOrder(nodePtr->left);
		preOrder(nodePtr->right);
	}

}

// postOrder - displays tree in postorder
void BST::postOrder(TNode *nodePtr) const {

	if (nodePtr) {
		postOrder(nodePtr->left);
		postOrder(nodePtr->right);
		cout << nodePtr->data << endl;
	}

}

// Inserts a new node into the binary search tree.
// Only able to insert a node with discrete data.
// If there is a node with same data as new data in the BST, new node cannot insert.
void BST::bstInsert(int data) {

	if (bstSearch(data)) {
		cout << "Data is already in the tree." << endl;
	} else {

		// Pointer to new node
		TNode *newNode = nullptr;

		// Create a new node and store num in it
		newNode = new TNode;
		newNode->data = data;
		newNode->left = newNode->right = nullptr;

		// Insert the node.
		insert(root, newNode);
	}
}

// Inserts the node.
void BST::insert(TNode *&nodePtr, TNode *&newNode) {
	
	if (nodePtr == nullptr)
		nodePtr = newNode; // Insert the node
	else if (newNode->data < nodePtr->data)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch
}

// Deletes a node from the binary search tree.
void BST::bstDelete(int num) {

	if (!bstSearch(num))
		cout << "Data is not in the tree & cannot be deleted." << endl;
	else
		deleteNode(num, root);
}

// Deletes the node.
void BST::deleteNode(int num, TNode *&nodePtr) {

	if (num < nodePtr->data)
		deleteNode(num, nodePtr->left);
	else if (num > nodePtr->data)
		deleteNode(num, nodePtr->right);
	else { // Actually make deletion.

		// Set temp pointer:
		TNode *temp = nullptr;

		if (nodePtr == nullptr)
			cout << "Cannot delete empty node." << endl;

		else if (nodePtr->right == nullptr) {

			temp = nodePtr;
			nodePtr = nodePtr->left;
			delete temp;

		} else if (nodePtr->left == nullptr) {

			temp = nodePtr;
			nodePtr = nodePtr->right;
			delete temp;

		} else {

			temp = nodePtr->right; // Move one node to the right

			// Go to end of left node
			while (temp->left) {
				temp = temp->left;

				temp->left = nodePtr->left; // Reattach left subtree
				temp = nodePtr;

				nodePtr = nodePtr->right; // Reattach right subtree
				delete temp;

			}

		}

	}
}

// Searches for a node in the binary search tree.
bool BST::bstSearch(int num) {

	TNode *nodePtr = root;

	while (nodePtr) {

		if (nodePtr->data == num)
			return true;
		else if (num < nodePtr->data)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}
