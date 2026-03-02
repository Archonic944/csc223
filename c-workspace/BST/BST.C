/* BST.C - Binary Search Tree implementation for BDS C
 * Based on Chapter 10: Efficient Binary Trees
 * Data Structures Using C, 2nd Ed. - Reema Thareja
 */

#include <stdio.h>
#include "BST.H"
#define NULL 0

/* Create a new node with the given value */
struct node *mknode(val)
int val;
{
    struct node *newnode;
    newnode = alloc(sizeof(struct node));
    newnode->data = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

/* Insert a value into the BST */
struct node *insert(tree, val)
struct node *tree;
int val;
{
    if (tree == NULL) {
        tree = mknode(val);
    }
    else if (val < tree->data) {
        tree->left = insert(tree->left, val);
    }
    else if (val > tree->data) {
        tree->right = insert(tree->right, val);
    }
    return tree;
}
