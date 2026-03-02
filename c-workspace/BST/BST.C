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
    newnode = alloc(6); /* int + 2 ptrs = 6 bytes on 8080 */
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

/* Search for a value in the BST */
struct node *search(tree, val)
struct node *tree;
int val;
{
    if (tree == NULL) {
        return NULL;
    }
    if (val == tree->data) {
        return tree;
    }
    else if (val < tree->data) {
        return search(tree->left, val);
    }
    else {
        return search(tree->right, val);
    }
}

/* In-order traversal: Left, Root, Right */
void inorder(tree)
struct node *tree;
{
    if (tree != NULL) {
        inorder(tree->left);
        printf("%d ", tree->data);
        inorder(tree->right);
    }
}

/* Pre-order traversal: Root, Left, Right */
void preorder(tree)
struct node *tree;
{
    if (tree != NULL) {
        printf("%d ", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

/* Post-order traversal: Left, Right, Root */
void postorder(tree)
struct node *tree;
{
    if (tree != NULL) {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->data);
    }
}

/* Find the node with the smallest value */
struct node *findmin(tree)
struct node *tree;
{
    if (tree == NULL) {
        return NULL;
    }
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

/* Find the node with the largest value */
struct node *findmax(tree)
struct node *tree;
{
    if (tree == NULL) {
        return NULL;
    }
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

/* Count total number of nodes */
int countnodes(tree)
struct node *tree;
{
    if (tree == NULL) {
        return 0;
    }
    return 1 + countnodes(tree->left) + countnodes(tree->right);
}

/* Delete a value from the BST.
 * Three cases:
 * 1. Node is a leaf - just remove it
 * 2. Node has one child - replace with child
 * 3. Node has two children - replace with inorder successor
 */
struct node *delete(tree, val)
struct node *tree;
int val;
{
    struct node *temp;
    if (tree == NULL) {
        printf("Value %d not found\n", val);
        return NULL;
    }
    if (val < tree->data) {
        tree->left = delete(tree->left, val);
    }
    else if (val > tree->data) {
        tree->right = delete(tree->right, val);
    }
    else {
        /* Found the node to delete */
        if (tree->left == NULL && tree->right == NULL) {
            /* Case 1: Leaf node */
            free(tree);
            return NULL;
        }
        else if (tree->left == NULL) {
            /* Case 2a: Only right child */
            temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL) {
            /* Case 2b: Only left child */
            temp = tree->left;
            free(tree);
            return temp;
        }
        else {
            /* Case 3: Two children
             * Replace with inorder successor (smallest in right subtree)
             */
            temp = findmin(tree->right);
            tree->data = temp->data;
            tree->right = delete(tree->right, temp->data);
        }
    }
    return tree;
}
