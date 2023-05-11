// Kalyn Howes
// 4.15.21
// Lab 9
// Red-Black Tree Class

#include "RBTree.h"
#include <iostream>
#include <iomanip> // setw

// colored output
#define RESET "\033[0m"
#define redText "\033[31m"
#define blueText "\033[34m"

// initialize nil
RBTree::TreeNode* const RBTree::nil = new TreeNode({0, BLACK, nullptr, nullptr, nullptr});

// constructor - takes in key value
RBTree::RBTree(int n) {
    TreeNode* temp = new TreeNode;
    temp->key = n;
    temp->color = BLACK;
    temp->left = nil;
    temp->right = nil;
    temp->parent = nil;

    root = temp;

    /*std::cout << "nil " << nil << std::endl;
    std::cout << "nil left: " << nil->left << std::endl;
    std::cout << "nil right: " << nil->right << std::endl;
    std::cout << "nil parent: " << nil->parent << std::endl;*/
}

// default constructor - sets key equal to 0
RBTree::RBTree() {
    root = nil;
}

/* copy constructor - this is so wrong do this instead:
// preorder traversal of arguement tree & insert into the new tree
RBTree::RBTree(const RBTree& T) {
    TreeNode* temp = new TreeNode;
    temp->key = T.root->key;
    temp->color = T.root->color;
    temp->left = T.root->left;
    temp->right = T.root->right;
    temp->parent = T.root->parent;

    root = temp;
}*/

// destructor
RBTree::~RBTree() {;
    destruct(root);
    root = nullptr;
    
    /* test printing:
    std::cout << "nil " << nil << std::endl;
    std::cout << "nil left: " << nil->left << std::endl;
    std::cout << "nil right: " << nil->right << std::endl;
    std::cout << "nil parent: " << nil->parent << std::endl;*/
    //delete nil;
    //nil = nullptr;
}

void RBTree::destruct(TreeNode *root) {
    if (root == nil)
        return;
    else {
        destruct(root->left);
        destruct(root->right);
        delete root;
    }
}

// adds new keys to the tree
// takes in a boolean - decides whether or not to print the inserts 1 by 1
void RBTree::insert(int k, bool print) {

    TreeNode* newNode = new TreeNode;
    newNode->key = k;

    TreeNode* y = nil;
    TreeNode* x = root;

    if (root == nil) {
        if (print)
            printf("Inserting %d into empty tree\n", k);
        root = newNode;
        newNode->parent = nil;
    } else {

        while (x != nil) {
            y = x;
            //std::cout << "\nIn while & y = x" << std::endl;

            if (newNode->key < x->key ) {
                //std::cout << "newNode  <  x" << std::endl;
                x = x->left;
            } else {
                //std::cout << "newNode  >= x" << std::endl;
                x = x->right;
            }
        }

        if (k < y->key) {
            if (print)
                printf("Inserting %d on the left of %d\n", k, y->key);
            y->left = newNode;
        } else {
            if (print)
                printf("Inserting %d on the right of %d\n", k, y->key);
            y->right = newNode;
        }
        newNode->parent = y;
      }
      newNode->color = RED;
      newNode->left = nil;
      newNode->right = nil;
      insertFix(newNode);
}

// fix-up routine for insert
void RBTree::insertFix(TreeNode *z) {
    
    TreeNode *y = NULL;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                z = z->parent;
                leftRotate(z);
                }

            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            rightRotate(z->parent->parent);
            }

        } else {
             y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                z = z->parent;
                rightRotate(z);
                }
            
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            leftRotate(z->parent->parent);
            
            }
        }
    }
    root->color = BLACK;
}

// returns the input nodes uncle (or parents sibling)
RBTree::TreeNode* RBTree::getUncle(TreeNode* x) {
	TreeNode* uncle = NULL;

	if (x != NULL && x != nil) {
		uncle = getGrandpa(x); //either NULL or grandparent
		if (uncle) {
			if (x->key > uncle->key)
				uncle = uncle->left; //either NULL or a NODE
			else
				uncle = uncle->right;
		}
	}
	return uncle;
}

// returns the input nodes grandparent (or parent->parent)
RBTree::TreeNode* RBTree::getGrandpa(TreeNode* x) {
	TreeNode* grandpa = new TreeNode;
	TreeNode* temp = x; // used to move around
	int i = 0; // used to loop twice, to get to grandparent
	do {
		if (temp) {
			if (temp->parent != NULL && temp->parent != nil)
				temp = temp->parent;
		}
		else // no parent exists there
			temp = NULL;
		i++;
	} while (i < 2);

	if (temp != NULL && temp != nil)
		grandpa = temp;
	return grandpa;
}

// allows the user to input a key in the main rather than an entire TreeNode
void RBTree::removeMain(int x) {
    TreeNode* temp = new TreeNode;
    temp = searchLocation(x);

    remove(temp);
}

// removes a given key from the tree, if it exists
void RBTree::remove(TreeNode *z) {
	TreeNode* x = new TreeNode;
	TreeNode* y = new TreeNode;

	if (z == NULL)
		std::cout << "This value is not in the Red-Black Tree..." << std::endl;
	else {
		// the node is in the tree
		if (z->right == nil || z->left == nil)
			y = z;
		else
			y = successor(z);

		if (y->left != nil)
			x = y->left;
		else
			x = y->right;

		x->parent = y->parent;

		if (x->parent == nil)
			root = x;
		else {
			// if y is left child
			if (y->parent != nil) {
				if (y->parent->left == y)
					y->parent->left = x;
				else
					y->parent->right = x;
			}
		}
		if (y != z)
			z->key = y->key;
		if (y->color == BLACK)
			removeFix(x);

	}
}

// fix-up routine for deleteNode
void RBTree::removeFix(TreeNode *x) {
    TreeNode *w = new TreeNode;

    while ( (x != root) && (x->color == BLACK) ) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if ( (w->left->color == BLACK) && (w->right->color == BLACK) ) {
                w->color = RED;
                x = x->parent;
            } else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = x->parent->right;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            leftRotate(x->parent);
            x = root;
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if ( (w->right->color == BLACK) && (w->left->color == BLACK) ) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                leftRotate(w);
                w = x->parent->left;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            rightRotate(x->parent);
            x = root;
        }
    }
    x->color = BLACK;
}

// searches the tree - given a key, determines whether there is a node with that key in the tree
// returns 0 for false or 1 if the key was found
bool RBTree::search(int x) {

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
RBTree::TreeNode* RBTree::searchLocation(int x) {
    TreeNode* u = root;
    while (u != NULL && u->key != x) {
        if (x < u->key) // go left
            u = u->left;
        else // go right
            u = u->right;
    }
    return u;
}

// minimum, which returns the smallest key in the tree - disregarding the nils
RBTree::TreeNode* RBTree::minimum(TreeNode* T) {
    TreeNode* u = T;

	if (u != nil && u != NULL) {
		while (u->left != nil)
			u = u->left;
	}

	return u;
}

// maximum, which returns the largest key in the tree - disregarding the 0s
RBTree::TreeNode* RBTree::maximum(TreeNode* T) {
   TreeNode* u = T;

	if (u != nil && u != NULL) {
		while (u->right != nil)
			u = u->right;
	}

	return u;
}

// allows the user to input a key in the main rather than an entire TreeNode
RBTree::TreeNode* RBTree::successorMain(int x) {
    TreeNode* temp = new TreeNode;
    temp = searchLocation(x);

    return (successor(temp));
}

// successor, for node with key k, returns the smallest key in the tree larger than k
RBTree::TreeNode* RBTree::successor(TreeNode* x) {
    TreeNode* temp = new TreeNode;

	if (x->right != NULL && temp != nil)
		temp = minimum(x->right);
	else {
		temp = x->parent;
		while (temp != nil && x == temp->right) {
			x = temp;
			temp = temp->parent; 
		}
	}
	return temp;
}

// inorder, which prints the keys in the tree in ascending order - disregards any nil
void RBTree::inorder(TreeNode* u) {
    if (u != NULL && u != nil) {
        inorder(u->left);
        printNode(u); // visit(u)
        inorder(u->right);
    }
}

// print - displays given key
void RBTree::printNode(TreeNode *u) {
    std::cout << u->key << " " << std::endl;
}

void RBTree::printInOrder(TreeNode* x) {
	if (x != nil) {
		printInOrder(x->left);
		if (x->key > 0) {
			if (x->color == RED)
				std::cout << " " << std::left << std::setw(8) << redText << x->key << RESET << std::endl;
			else
				std::cout << " " << std::left << std::setw(8) << blueText << x->key  << RESET << std::endl;
		} else {
			if (x->color == RED)
				std::cout << " " << std::left << std::setw(9) << redText << x->key << RESET << std::endl;
			else
				std::cout << " " << std::left << std::setw(9) << blueText << x->key << RESET << std::endl;
		}
		printInOrder(x->right);
	}
}

void RBTree::printPreOrder(TreeNode* x) {
	if (x != nil)
	{
		if (x->key > 0) {
			if (x->color == RED)
				std::cout << " " << std::left << std::setw(8) << redText << x->key << RESET << std::endl;
			else
				std::cout << " " << std::left << std::setw(8) << blueText << x->key << RESET << std::endl;
		}
		else {
			if (x->color == RED)
				std::cout << " " << std::left << std::setw(9) << redText << x->key << RESET << std::endl;
			else
				std::cout << " " << std::left << std::setw(9) << blueText << x->key << RESET << std::endl;
		}
	    printPreOrder(x->left);
		printPreOrder(x->right);
	}
}

// -------- PRIVATE FUNCTIONS --------

void RBTree::rightRotate(TreeNode *x) {
    RBTree::TreeNode *y = new TreeNode;

    y = x->left;
    x->left = y->right;

    if (y->right != nil)
        y->right->parent = x;
    
    y->parent = x->parent;

    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else 
        x->parent->left = y;
    
    y->right = x;
    x->parent = y;
}

void RBTree::leftRotate(TreeNode *x) {
    RBTree::TreeNode *y = new TreeNode;

    y = x->right;
    x->right = y->left;

    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}
    
void RBTree::transplant(TreeNode *u, TreeNode *v) {
    
    if (u->parent == nil)
        root = v;
    else if (u->parent->right == v)
        u->parent->left = v;
    else 
        u->parent->right = v;

    v->parent = u->parent;
}