// BST_STRINGS.C 
// Example building binary search tree. This version uses both key and value
// field, with both fields being strings.
// This code displays a lot of information as it works. You may find it
// informative to use the information to follow how the tree is built.


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



//
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Tree node definition
typedef struct _trnode	TreeNode, *pTreeNode;

struct _trnode	{
	char		*pname;			// name of parameter
	char		*pvalue;		// value of parameter
	TreeNode	*leftChild;		// pointer to left subtree
	TreeNode	*rightChild;	// pointer to right subtree
};

#define SZ_TRNODE	(sizeof (TreeNode))

TreeNode *CreateNode (char *key, char *value)
// Create new node with key and value passed as string parameters. Copies are
// made of strings passed. Node can be created without value, but key is
// required. Key-only nodes useful for binary data - key exists or it doesn't.
{
	TreeNode	*pn = NULL;

	// Parameter check first. Insist on key, but accept value if it is NULL.
	// Allows for parameters inform by either existing or not existing.
	if (key != NULL)	{
		pn = (TreeNode *) malloc (SZ_TRNODE);
		if (pn)	{
			pn->pname = strdup (key);
			pn->pvalue = value==NULL ? NULL : strdup (value);
			pn->leftChild = NULL;
			pn->rightChild = NULL;
			}
		}//if at least key was provided
	return pn;
}//initNode()


int DeleteNode (TreeNode *ptn)
// Delete TreeNode structure.  Only deals with one structure; does not delete
// left or right subtrees if they exist. (They should already have been dealt
// with before node is deleted.
{
	int		rslt = -1;
	if (ptn != NULL)	{
		free (ptn->pname);			// give up space for name
		if (ptn->pvalue != NULL)	// is there explicit parameter value?
			free (ptn->pvalue);		// give up space for parameter value
		// dta has been discarded, now discard actual node
		free (ptn);
		rslt = 0;
		}
	return rslt;
}//DeleteNode()


int CompareNodes (TreeNode *psrc, TreeNode *pdst, int *prslt)
// Comparison routine used to order nodes. Given two nodes, compares key values
// using strcmp(), result is returned in variable pointed to by prslt.
// Function returns -1 if something failed, 0 otherwise.
{
	if ((psrc == NULL) || (pdst == NULL) || (prslt == NULL))	return -1;
	*prslt = strcmpi (psrc->pname, pdst->pname);
	return 0;
}//CompareNodes()

	

// Structure definition for a Tree.
// Tree is basically pointer to top node in a tree.
typedef struct _tree {
	TreeNode *root;
} Tree;


// ----------------------------------------------------------------------------

// Code to create and manage trees and treenodes

// This code is only going to use one tree - declare it now.
Tree	mytree = {NULL};




int insert_node (TreeNode *pnew, TreeNode **proot)
// Insert node pointed to by pnew into tree that has its root node pointed to
// by pointer pointed to by proot. (Referring to the diagram above, proot will
// be a pointer to "root", or "left" in the node or "right" in the node - all
// pointers to trees [or subtrees])
{
	TreeNode	*pr;
	int		rslt = -1;		// default return value is failure
	int		cmprslt;		// hold result of comparisons

	// Check for obvious errors
	if ((proot == NULL) || (pnew == NULL))	return rslt;
	// Trivial case - tree pointed to by pointer that proot points to is empty
	// and we're inserting first node into this tree
	if (*proot == NULL)	{
		*proot = pnew;		// think about where value pn is assigned -
							// not to proot, but to location that proot
							// points to.
		rslt = 0;			// insert worked
		printf (" --- Value %s inserted at root\n", pnew->pname);
	} else	{
		// Non trivial case - have to find where node is to go. Take into
		// consideration whether new node has smaller or larger value than
		// existing one.
		pr = *proot;		// get pointer to node - makes things easier
		// Now determine whether new node value is less than, greater than or
		// equal to current root node value. Equal is rejected.
		if (CompareNodes (pnew, pr, &cmprslt) == 0)	{
			if (cmprslt > 0)	{
				// value being inserted belongs in right subtree
				printf (" --- %s goes into Right subtree of value %s\n",
					pnew->pname, pr->pname);
				rslt = insert_node (pnew, &(pr->rightChild));
			} else if (cmprslt < 0)	{
				// value being inserted belongs in left subtree
				printf (" --- %s goes into Left subtree of value %s\n",
					pnew->pname, pr->pname);
				rslt = insert_node (pnew, &(pr->leftChild));
				}
			}//endif compare successful
		}
		// Note that, by default, if values are same, rslt is still -1
	return rslt;
}//insert_node()


void print_preorder (TreeNode *pn)
// Print tree values based on preorder traversal. Function gets pointer to
// node, then prints node value, left subtree, right subtree.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	printf (" %s\n ", pn->pname);
	print_preorder (pn->leftChild);
	print_preorder (pn->rightChild);
}//print_preorder()
	

void print_postorder (TreeNode *pn)
// Print tree values based on postorder traversal. Function gets pointer to
// node, then prints left subtree, right subtree, node value.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	print_postorder (pn->leftChild);
	print_postorder (pn->rightChild);
	printf (" %s\n", pn->pname);
}//print_postorder()


void print_inorder (TreeNode *pn)
// Print tree values based on inorder traversal. Function gets pointer to
// node, then prints left subtree, node value, right subtree.
{
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return;
	print_inorder (pn->leftChild);
	printf (" %s\n", pn->pname);
	print_inorder (pn->rightChild);
}//print_inorder()



int main (int argc, char *argv[], char *environ[])
// Test code to illustrate how binary search tree works with key and data
// being strings. We use a test file that resembles a DOS/Windows system
// configuration (INI) file.
{
	int			i;
	TreeNode	*pnode;
	int			rslt;
	char		*p, *pname, *pvalue;
	FILE		*fp;
	char		*pbuff;

	// Get buffer to read data file into.
	pbuff = (char *)malloc (256);
	if (pbuff == NULL)	{
		fprintf (stderr, "ERROR: Cannot get memory for buffer\n");
		return -1;
		}
	fp = fopen ("TEST.ini", "r");
	if (fp == NULL)	{
		fprintf (stderr, "ERROR: Cannot open data file\n");
		return -1;
		}
	for (;;)	{
		p = fgets (pbuff, 256, fp);
		if (p == NULL)	break;
		while (*p == ' ')	p++;
		pname = p;
		p++;
		while (*p != '=')	p++;
		*p = '\0';
		p++;
		while (*p == ' ')	p++;
		pvalue = p;
		p++;
        while (*p != '\n' && *p != '\r') p++;
		*p = '\0';
		printf ("Name: %15s   Value: %s\n", pname, pvalue);
		pnode = CreateNode (pname, pvalue);
		insert_node (pnode, &mytree.root);
		}
	fclose (fp);

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




