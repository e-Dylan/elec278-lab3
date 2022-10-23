// BST_TRAVERSAL.C 
// Simple example building binary search tree.  This code only illustrates how
// one might build a BST with a single integer as data (used also as the key),
// and how tree traversals work.
//
// Review code carefully and be sure you understand the double pointers used.
//
// Main points:
//		Look at simplified structure used to point to top of tree.
//		Look at simplified version of tree node - just one piece of data used to
//		control the ordering.
//
//


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2022.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.


All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */



#include <stdlib.h>
#include <stdio.h>

// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Structure definition for tree node.
// This is bare minimum needed for binary tree - two pointers to subtrees
// and one item of data. Most useful trees will contain more.
// (Note how the definition includes the definition of the node structure AND
// typedefs so that I don't have to type struct all the time. Note also I have
// defined pNode as a pointer to a struct node, and ppNode as a pointer to a
// pointer to a struct node.  We'll see why these are useful when we implement
// the function to insert new data into the tree.  The following diagram may
// be helpful.
//
//    ppNode         pNode root     Node
//    +-------+      +-------+      +--------+
//    |     o------->|     o------->| value  |
//    +-------+      +-------+      +--------+
//                                  |  left  |
//                                  +/-------+
//                                  / right  |
//                                 /+-------\+
//                                /          \
//                            left           right
//                           subtree        subtree


typedef struct node	{
	int				value;
	struct node		*leftChild, *rightChild ;
} Node, *pNode, **ppNode;

#define SZ_NODE	(sizeof (struct node))

// Code related specifically to nodes - routines to allocate and to delete
// tree nodes

Node *initNode (int v)
// Create new node with value field set to v and pointers initialized to NULL.
// Returns pointer to newly created node, or NULL if no memory could be
// allocated.
{
	Node	*pn;
	pn = (Node *) malloc (SZ_NODE);
	if (pn)	{
		pn->value = v;
		pn->leftChild = NULL;
		pn->rightChild = NULL;
		}
	return pn;
}//initNode()


// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Structure definition for Tree.
// Tree is basically pointer to root node in tree.
typedef struct Tree
{
	Node *root;
} Tree;

// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*


// This code is only going to use one tree - declare it now, with a NULL
// pointer.
Tree	mytree = {NULL};


// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*


int insert_node (Node *pnew, Node **proot)
// Insert node pointed to by pnew into tree that has its root node pointed to
// by pointer pointed to by proot. (Referring to the diagram above, proot will
// be a pointer to "root", or "left" in the node or "right" in the node - all
// pointers to trees [or subtrees])
{
	Node	*pr;
	int		rslt = -1;		// default return value is failure

	// Check for obvious errors
	if (proot == NULL || pnew == NULL)	return rslt;
	// Trivial case - tree pointed to by pointer that proot points to is empty
	// and we're inserting first node into this tree
	if (*proot == NULL)	{
		*proot = pnew;		// think about where the value pn is assigned -
							// not to proot, but to the location that proot
							// points to.
		rslt = 0;			// insert worked
		printf (" --- Value %d inserted at root of subtree\n", pnew->value);
	} else	{
		// Non trivial case - have to find where node is to go. Take into
		// consideration whether new node has smaller or larger value than
		// existing one.
		pr = *proot;		// get pointer to node - makes things easier
		// Now determine whether new node value is less than, greater than or
		// equal to current root node value. Equal is rejected.
		if (pnew->value > pr->value)	{
			// value being inserted belongs in right subtree
			printf (" --- %d goes into Right subtree of value %d\n",
					pnew->value, pr->value);
			rslt = insert_node (pnew, &(pr->rightChild));
		} else if (pnew->value < pr->value)	{
			// value being inserted belongs in left subtree
			printf (" --- %d goes into Left subtree of value %d\n",
					pnew->value, pr->value);
			rslt = insert_node (pnew, &(pr->leftChild));
			}
		}
		// Note that, by default, if the values are the same, rslt is still -1
	return rslt;
}//insert_node()


void print_preorder (Node *pn)
// Print tree values based on preorder traversal. Function gets pointer to
// node, then prints node value, left subtree, right subtree.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	printf (" %d ", pn->value);
	print_preorder (pn->leftChild);
	print_preorder (pn->rightChild);
}//print_preorder()
	

void print_postorder (Node *pn)
// Print tree values based on postorder traversal. Function gets pointer to
// node, then prints left subtree, right subtree, node value.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	print_postorder (pn->leftChild);
	print_postorder (pn->rightChild);
	printf (" %d ", pn->value);
}//print_postorder()


void print_inorder (Node *pn)
// Print tree values based on inorder traversal. Function gets pointer to
// node, then prints left subtree, node value, right subtree.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	print_inorder (pn->leftChild);
	printf (" %d ", pn->value);
	print_inorder (pn->rightChild);
}//print_inorder()


void print_compressed ()
{
}


// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Code to test implementation. First is some data that will be used to build
// trees.

// YOU HAVE TO REMOVE COMMENT INDICATOR FROM ONE OF THE FOLLOWING LINES
//#define USE_ARBITRARY
#define USE_CLASS_DATA

#ifdef USE_ARBITRARY
// Just random set of integers
#define	DATASZ	20
int data [20]	=	{
	55, 62, 47, 12, 56,	72, 99, 18, 43, 51,
	38, 83, 41, 16, 15, 66, 91, 81, 71, 61
	};
#endif

#ifdef USE_CLASS_DATA
// This is the data used in class
#define	DATASZ	14
int data [14]	=	{
	28,  15,  37,   4,  25,  32,  46,  3,  12,  20,
    30,  34,  14,  23
	};
#endif


int main (void)
// Test code to illustrate how binary search tree works
{
	int		i;
	Node	*pnode;
	int		rslt;
	
	for (i=0; i<DATASZ; i++)	{
		printf ("Inserting value %d into BST\n", data[i]);
		// First build node with value
		pnode = initNode (data[i]);
		// and insert the node into the tree
		rslt = insert_node (pnode, &mytree.root);
		if (rslt)	{
			printf ("Problem inserting %d\n", data[i]);
			}
		}//endfor

	// now show that we have a BST
	printf ("Inorder Traversal\n");
	print_inorder(mytree.root);
	printf ("\n----------\n");
	printf ("Preorder Traversal\n");
	print_preorder(mytree.root);
	printf ("\n----------\n");
	printf ("Postorder Traversal\n");
	print_postorder(mytree.root);
	printf ("\n----------\n");
	return 0;
}//main()




