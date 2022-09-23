// Kalyn Howes
// 4.15.21
// Lab 9
// Red-Black Tree Class - header file

#ifndef RBTree_H
#define RBTree_H

#include <iostream>

class RBTree {
    private:

        // where the type color_t is defined by the enum type
        enum color_t {
            RED,
            BLACK
        };

        struct TreeNode {
            int key;
            color_t color;
            TreeNode* left;
            TreeNode* right;
            TreeNode* parent;

            // default constructor
            TreeNode() {
                key = 0;
                color = BLACK;
                left = nil;
                right = nil;
                parent = nil; 
            }

            // constructor
            TreeNode(int i, color_t c, TreeNode* l, TreeNode* r, TreeNode* p): key(i), color(c), left(l), 
            right(r), parent(p) {}

        };
    
        static TreeNode* const nil;
        TreeNode* root;

        // define as private methods the Red-Black Tree helper methods Right-Rotate, Left-Rotate, and transplant:
        void rightRotate(TreeNode*);
        void leftRotate(TreeNode*);
        void transplant(TreeNode*, TreeNode*);


    public:

        RBTree(int); // constructor
        RBTree(); // default constructor
        RBTree(const RBTree&);
        ~RBTree(); // destructor
        void destruct(TreeNode*);

        TreeNode* getRoot() { return root; } // accessor

        // assignment overload...?
        TreeNode* operator=(const TreeNode* T) { TreeNode *ret = new TreeNode; ret->left = T->left; ret->right = T->right;
        ret->parent = T->parent; ret->color = T->color; ret->key = T->key; return ret; }

        void insert(int, bool);
        void insertFix(TreeNode*);

        TreeNode* getUncle(TreeNode* x);
        TreeNode* getGrandpa(TreeNode* x);

        void removeMain(int);
        void remove(TreeNode*);
        void removeFix(TreeNode*);

        bool search(int);
        TreeNode* searchLocation(int);

        TreeNode* minimum(TreeNode*);
        TreeNode* maximum(TreeNode*);

        TreeNode* successorMain(int);
        TreeNode* successor(TreeNode*);

        void inorder(TreeNode*);
        void printNode(TreeNode*);
        void printInOrder(TreeNode*);
        void printPreOrder(TreeNode*);

};

#endif
