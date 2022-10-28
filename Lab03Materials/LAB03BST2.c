// LAB03BST2.c - Lab 03 - Dylan, Smith

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Tree node definition
typedef struct _trnode Node, *pTreeNode;

struct _trnode
{
	char *pkey;		  // name of parameter
	char *pvalue;	  // value of parameter
	Node *leftChild;  // pointer to left subtree
	Node *rightChild; // pointer to right subtree
};

#define SZ_TRNODE (sizeof(Node))

Node *CreateNode(char *key, char *value)
// Create new node with key and value passed as string parameters. Copies are
// made of strings passed. Node can be created without value, but key is
// required. Key-only nodes useful for binary data - key exists or it doesn't.
{
	Node *pn = NULL;

	// Parameter check first. Insist on key, but accept value if it is NULL.
	// Allows for parameters inform by either existing or not existing.
	if (key != NULL)
	{
		pn = (Node *)malloc(SZ_TRNODE);
		if (pn)
		{
			pn->pkey = strdup(key);
			pn->pvalue = value == NULL ? NULL : strdup(value);
			pn->leftChild = NULL;
			pn->rightChild = NULL;
		}
	} // if at least key was provided
	return pn;
} // initNode()

int DeleteNode(Node *ptn)
// Delete Node structure.  Only deals with one structure; does not delete
// left or right subtrees if they exist. (They should already have been dealt
// with before node is deleted.
{
	int rslt = -1;
	if (ptn != NULL)
	{
		free(ptn->pkey);		 // give up space for name
		if (ptn->pvalue != NULL) // is there explicit parameter value?
			free(ptn->pvalue);	 // give up space for parameter value
		// dta has been discarded, now discard actual node
		free(ptn);
		rslt = 0;
	}
	return rslt;
} // DeleteNode()

int CompareNodes(Node *psrc, Node *pdst, int *prslt)
// Comparison routine used to order nodes. Given two nodes, compares key values
// using strcmp(), result is returned in variable pointed to by prslt.
// Function returns -1 if something failed, 0 otherwise.
{
	if ((psrc == NULL) || (pdst == NULL) || (prslt == NULL))
		return -1;
	*prslt = strcmpi(psrc->pkey, pdst->pkey);
	return 0;
} // CompareNodes()

// Structure definition for a Tree.
// Tree is basically pointer to top node in a tree.
typedef struct _tree
{
	Node *root;
} Tree;

int insert_node(Node *pnew, Node **proot)
// Insert node pointed to by pnew into tree that has its root node pointed to
// by pointer pointed to by proot. (Referring to the diagram above, proot will
// be a pointer to "root", or "left" in the node or "right" in the node - all
// pointers to trees [or subtrees])
{
	Node *pr;
	int rslt = -1; // default return value is failure
	int cmprslt;   // hold result of comparisons

	// Check for obvious errors
	if ((proot == NULL) || (pnew == NULL))
		return rslt;
	// Trivial case - tree pointed to by pointer that proot points to is empty
	// and we're inserting first node into this tree
	if (*proot == NULL)
	{
		*proot = pnew; // think about where value pn is assigned -
					   // not to proot, but to location that proot
					   // points to.
		rslt = 0;	   // insert worked
					   // printf(" --- Value %s inserted at root\n", pnew->pkey);
	}
	else
	{
		// Non trivial case - have to find where node is to go. Take into
		// consideration whether new node has smaller or larger value than
		// existing one.
		pr = *proot; // get pointer to node - makes things easier
		// Now determine whether new node value is less than, greater than or
		// equal to current root node value. Equal is rejected.
		if (CompareNodes(pnew, pr, &cmprslt) == 0)
		{
			if (cmprslt > 0)
			{
				// value being inserted belongs in right subtree
				// printf(" --- %s goes into Right subtree of value %s\n",
				//    pnew->pkey, pr->pkey);
				rslt = insert_node(pnew, &(pr->rightChild));
			}
			else if (cmprslt < 0)
			{
				// value being inserted belongs in left subtree
				// printf(" --- %s goes into Left subtree of value %s\n",
				//    pnew->pkey, pr->pkey);
				rslt = insert_node(pnew, &(pr->leftChild));
			}
		} // endif compare successful
	}
	// Note that, by default, if values are same, rslt is still -1
	return rslt;
} // insert_node()

int isValid(Node *root)
{
	if (root == NULL)
		return 1;

	if (root->leftChild != NULL && root->leftChild->pkey > root->pkey)
		return 0;

	if (root->rightChild != NULL && root->rightChild->pkey < root->pkey)
		return 0;

	if (!isValid(root->leftChild) || !isValid(root->rightChild))
		return 0;

	// BST is valid
	return 1;
}

int main(void)
{
	Tree t = {NULL};

	int i;
	Node *pnode;
	int rslt;
	char *p, *pkey, *pvalue;
	FILE *fp;
	char *pbuff;

	// Get buffer to read data file into.
	pbuff = (char *)malloc(256);
	if (pbuff == NULL)
	{
		fprintf(stderr, "ERROR: Cannot get memory for buffer\n");
		return -1;
	}
	fp = fopen("IDENTS_SMALL.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "ERROR: Cannot open data file\n");
		return -1;
	}

	int num_nodes = 0;

	for (;;)
	{
		// Extract each line
		p = fgets(pbuff, 256, fp);
		if (p == NULL)
			break;

		// Split the line string into two strings for each id and password
		char *id = strtok(p, " ");
		// printf("%s", id);
		char *pwd = strtok(NULL, " ");
		// printf(" %s\n", pwd);

		// Create node with key and val and insert into tree
		pnode = CreateNode(id, pwd);
		insert_node(pnode, &t.root);
		num_nodes++;
	}
	printf("BST NODES: %d", num_nodes);

	// This returns a warning for incompatible pointer type, not sure why.
	// don't have time to debug.
	if (!isValid(&t.root))
	{
		return 0;
	}
	// Close file when done reading
	fclose(fp);
}