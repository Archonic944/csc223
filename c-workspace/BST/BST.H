/* BST.H - Binary Search Tree header for BDS C
 * Based on Chapter 10: Efficient Binary Trees
 * Data Structures Using C, 2nd Ed. - Reema Thareja
 */

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *insert();
struct node *delete();
struct node *search();
struct node *mknode();
struct node *findmin();
struct node *findmax();
void inorder();
void preorder();
void postorder();
int countnodes();
