# Red-Black Tree

## Examples

![Red black tree](image-4.png)

![Every path doesn't have same amount of black children](image-6.png)

## Internal Representation

In a red-black tree, no data is stored in the leaf nodes. The leaf nodes are just placeholders to make the tree complete. One bit is required for each node to indicate whether it is red or black. If you're smart, you can combine the bit with the data to save on memory.

## Rotations

A rotation alters the structure of the tree in order to decrease its height. Larger subtrees are moved up the tree, and smaller subtrees are moved down.

Rotations never change the order of the elements.

### Left Rotation

![Left rotation diagram](image-7.png)

### Right Rotation

![Right rotation diagram](image-8.png)

### Pseudo-code example

![pseudocode](image-9.png)

## Handling Deletions



## Code & Visualization

