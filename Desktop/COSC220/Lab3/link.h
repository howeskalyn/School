// Kalyn Howes
// 9.29.20
// link.h: header file for a node data structure and function prototypes.

#ifndef LINK_H_
#define LINK_H_

struct node {
	char lastName[20];
	char firstName[20];
	int idNumber;
	node *next;
};

node* createNode();
node* insertNode(node*, node*);
node* searchNode(node*, int);
node* deleteNode(node*, int);
void printList(node*);

#endif
