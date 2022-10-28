// MAIN.C
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

#include "Lab3_bst.c"

// Code for ELEC278 Lab exercise 3.
//
// The lab requires that you implement 3 functions:
//	int height (Node *);
//	Node* findParentHelper (Key, Node*);
//	delete (Node*, Node*);
//
// NOTE: The following 3 lines define preprocessor labels or manifests.  They
// are set to 0 in the distribution.  If you check code in main(), you will
// see #if statements that check values.  When you set a manifest here to 1,
// the corresponding code in main will be executed.
#define HEIGHT_WRITTEN 1
#define FINDPARENTHELPER_WRITTEN 1
#define DELETE_WRITTEN 1
//
// *** YOU SHOULD NOT MAKE ANY OTHER CHANGES TO THIS CODE ***

int main(void)
{
    Node *n = NULL; // eliminates compiler warning
    int v1 = 1;
    Tree *t = initTree(10, &v1);
    // Note: This implementation requires that tree be initialized with first
    // node.
    insert(10, &v1, t->root);
    insert(3, &v1, t->root);
    insert(1, &v1, t->root);
    insert(7, &v1, t->root);
    insert(20, &v1, t->root);
    insert(15, &v1, t->root);
    insert(18, &v1, t->root);
    insert(17, &v1, t->root);
    insert(16, &v1, t->root);

    printf("Original Tree: \n");
    printTree(t->root);
    printf("\n\n");

    if (HEIGHT_WRITTEN == 1)
    {
        printf("Height of tree: %d\n\n", height(t->root));
    }

    if (FINDPARENTHELPER_WRITTEN == 1)
    {
        printf("Parent of root (key=10): %d\n", findParent(10, t->root)->key);
        printf("Parent of leaf (key=16): %d\n", findParent(16, t->root)->key);
        printf("Parent of other (key=15): %d\n\n", findParent(15, t->root)->key);
    }

    if (DELETE_WRITTEN == 1)
    {
        printf("Tree after deleting 1:\n");
        withdraw(1, t->root, n);
        printTree(t->root);
        printf("\n\n");
        // free (n);
        printf("Tree after deleting 3:\n");
        withdraw(3, t->root, n);
        printTree(t->root);
        printf("\n\n");
        // free(n);

        printf("Tree after deleting 20:\n");
        withdraw(20, t->root, n);
        printTree(t->root);
        printf("\n");
        // free(n);
    }

    return 0;
} // main()
