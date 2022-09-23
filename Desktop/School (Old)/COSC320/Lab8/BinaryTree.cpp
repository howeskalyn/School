// Kalyn Howes
// 4.1.21
// Lab 8
// Binary Tree Class

#include "BinaryTree.h"
#include <iostream>
#include <iomanip> // setw

// constructor - takes in key value
BinaryTree::BinaryTree(int n) {
    root->key = n; 
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
}

// default constructor - sets key equal to 0
BinaryTree::BinaryTree() {
    root->key = 0;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
}

// destructor
BinaryTree::~BinaryTree() {
    //destroy(root);
}

void BinaryTree::destroy(TreeNode *root) {
    if (root == nullptr)
        return;
    else {
        destroy(root->left);
        destroy(root->right);
        delete root;
        root = nullptr;
    }
}

//insert, to add a new key to the tree.
void BinaryTree::insert(int key) {
    size++;

    TreeNode *newNode = new TreeNode;
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;

    // if empty tree
    if (root == nullptr) {
        root = newNode;
        newNode->parent = nullptr;
    } else {
        TreeNode *temp = nullptr;
        TreeNode *current = root;

        while (current != nullptr) {
            temp = current;

            if (key < current->key) 
                current = current->left;
            else if (key > current->key || key == current->key)
                current = current->right;
        }

        newNode->parent = temp;

        if (newNode->key < temp->key) 
            temp->left = newNode;
        else if (newNode->key > temp->key)
            temp->right = newNode;
    }
}

// searches the tree - given a key, determines whether there is a node with that key in the tree
// returns 0 for false or 1 if the key was found
bool BinaryTree::search(int x) {

    TreeNode* temp = root;
	bool found = false; // holds return

	while (!found && temp != NULL) {
		if (temp->key < x) { // go right
			temp = temp->right;

        } else if (temp->key > x) { // go left
			temp = temp->left;

        } else if (temp->key == x) { // equal - its found!
			found = true;

        } else if (temp == NULL) // end of tree - false is returned
			break;
	}

	return found;
}

// finds the TreeNode in which the key parameter is in
BinaryTree::TreeNode* BinaryTree::searchLocation(int x) {
    TreeNode* u = root;
    while (u != NULL && u->key != x) {
        if (x < u->key) // go left
            u = u->left;
        else // go right
            u = u->right;
    }
    return u;
}

// minimum, which returns the smallest key in the tree
BinaryTree::TreeNode* BinaryTree::minimum(TreeNode* T) {
    TreeNode *u = new TreeNode;
    u = T;

    while (u->left != NULL)
        u = u->left;
    return u;
}

// maximum, which returns the largest key in the tree
BinaryTree::TreeNode* BinaryTree::maximum(TreeNode* T) {
    TreeNode *u = new TreeNode;
    u = T;

    while (u->right != NULL)
        u = u->right;
    return u;
}

// allows the user to input a key in the main rather than an entire TreeNode
BinaryTree::TreeNode* BinaryTree::successorMain(int x) {
    TreeNode* temp = new TreeNode;
    temp = searchLocation(x);

    return (successor(temp));
}

// successor, for node with key k, returns the smallest key in the tree larger than k
BinaryTree::TreeNode* BinaryTree::successor(TreeNode* x) {
    TreeNode *temp = new TreeNode;

    if (x->right != NULL)
        return minimum(x->right);
    else {
        temp = x->parent;
        while (temp != NULL && x == temp->right) {
            x = temp;
            temp = temp->parent;
        }
    }
    return x;
}

// inorder, which prints the keys in the tree in ascending order
void BinaryTree::inorder(TreeNode* u) {
    if (u != NULL) {
        inorder(u->left);
        printNode(u); // visit(u)
        inorder(u->right);
    }
}

// allows the user to input a key in the main rather than an entire TreeNode
void BinaryTree::removeMain(BinaryTree T, int x) {
    TreeNode* temp = new TreeNode;
    temp = searchLocation(x);

    remove(T, temp);
}

// delete, which removes a given key from the tree, if it exists
void BinaryTree::remove(BinaryTree T, TreeNode *x) {
    size--;
    TreeNode *temp = new TreeNode;

    if (T.search(x->key) == 0)
		std::cout << "The key " << x->key << " is NOT in the binary search tree." << std::endl;
    else if (T.search(x->key) == 1) {
            std::cout << "The key " << x->key << " is in the tree, the deleting process is starting now." << std::endl;

        if (x->left == NULL)
            transplant(T, x, x->right);

        else if (x->right == NULL) // x has exactly 1 child since the above is false
            transplant(T, x, x->left);

        else { // both children
            temp = successor(x); // y = min(x.right)
            if (temp->parent != x) {
                transplant(T, temp, temp->right);
                temp->right = x->right;
                temp->right->parent = temp; // clean up
            }
            transplant(T, x, temp); 
            temp->left = x->left;
            temp->left->parent = temp; // clean up
        }
    }
}

// helper for delete, replaces subtree rooted at u with subtree rooted at v
void BinaryTree::transplant(BinaryTree T, TreeNode *u, TreeNode *v) {
    if (u->parent == NULL)
        T.root = v;
    else { // link v to u's parent on correct side
        if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
    }

    if (v != NULL)
        v->parent = u->parent;
}


// print - displays given key
void BinaryTree::printNode(TreeNode *u) {
    std::cout << u->key << " " << std::endl;
}

// prints the tree in order
void BinaryTree::printInOrder(TreeNode* x) {
	if (x != NULL) {
		printInOrder(x->left);
		if (x->key > 0)
			std::cout << " " << std::left << std::setw(8) << x->key << std::endl;
		else
			std::cout << std::left << std::setw(9) << x->key << std::endl;
		printInOrder(x->right);
	}
}