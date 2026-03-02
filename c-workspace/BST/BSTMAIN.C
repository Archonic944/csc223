/* BSTMAIN.C - Menu-driven Binary Search Tree program
 * Based on Chapter 10 programming example (pp. 306-311)
 * Data Structures Using C, 2nd Ed. - Reema Thareja
 * Adapted for BDS C / CP/M on Altair 8800
 */

#include <stdio.h>
#include "BST.H"
#define NULL 0

main()
{
    struct node *root;
    struct node *result;
    int choice, val;

    root = NULL;

    while (1) {
        printf("\n--- Binary Search Tree Menu ---\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Search for a value\n");
        printf("4. In-order traversal\n");
        printf("5. Pre-order traversal\n");
        printf("6. Post-order traversal\n");
        printf("7. Find smallest element\n");
        printf("8. Find largest element\n");
        printf("9. Count total nodes\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &val);
            root = insert(root, val);
            printf("%d inserted\n", val);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &val);
            root = delete(root, val);
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &val);
            result = search(root, val);
            if (result != NULL) {
                printf("%d found in the tree\n", val);
            } else {
                printf("%d not found\n", val);
            }
            break;

        case 4:
            printf("In-order: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            printf("Pre-order: ");
            preorder(root);
            printf("\n");
            break;

        case 6:
            printf("Post-order: ");
            postorder(root);
            printf("\n");
            break;

        case 7:
            result = findmin(root);
            if (result != NULL) {
                printf("Smallest: %d\n", result->data);
            } else {
                printf("Tree is empty\n");
            }
            break;

        case 8:
            result = findmax(root);
            if (result != NULL) {
                printf("Largest: %d\n", result->data);
            } else {
                printf("Tree is empty\n");
            }
            break;

        case 9:
            printf("Total nodes: %d\n", countnodes(root));
            break;

        case 10:
            printf("Goodbye!\n");
            exit();

        default:
            printf("Invalid choice\n");
            break;
        }
    }
}
