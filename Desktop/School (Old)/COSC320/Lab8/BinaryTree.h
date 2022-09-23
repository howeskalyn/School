// Kalyn Howes
// 4.2.21
// Lab 8
// Binary Tree Class - header file

#ifndef BinaryTree_H
#define BinaryTree_H

#include <iostream>

class BinaryTree {

    private:
        struct TreeNode {
            int key; // value in the node
            TreeNode* left; // left child
            TreeNode* right; // right child
            TreeNode* parent; // node above 
        };

        TreeNode* root = new TreeNode;
        int size = 0;
        void transplant(BinaryTree, TreeNode*, TreeNode*); // used in delete
        // may include other private methods to carry out the “standard” recursive behavior, such as inorder traversal

    public:
    BinaryTree(int); // constructor
    BinaryTree(); // default constructor
    ~BinaryTree(); // destructor
    void destroy(TreeNode*);
    TreeNode* getRoot() { return root; } // accessor

    void insert(int);

    bool search(int);
    TreeNode* searchLocation(int);
    TreeNode* minimum(TreeNode*);
    TreeNode* maximum(TreeNode*);

    TreeNode* successorMain(int);
    TreeNode* successor(TreeNode*);

    void inorder(TreeNode*);

    void removeMain(BinaryTree, int);
    void remove(BinaryTree, TreeNode*);

    void printNode(TreeNode*);
    void printInOrder(TreeNode*);
};

#endif