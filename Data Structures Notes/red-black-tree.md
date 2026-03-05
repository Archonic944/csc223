# Red-Black Tree

## Examples

Red black tree:

![Red black tree](image-4.png)

Not a red black tree:

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

First, you must delete the node as you do in a standard binary search tree. If the node is a leaf, you simply remove it. If the node has one child, you replace the node with its child. If it has two children, you replace the node with its in-order successor (the smallest node in the right subtree) and then delete the in-order successor.

If the deleted node is red, then the tree is still a valid red-black tree.

If the deleted node is black, the tree likely now violates red-black properties. For example: 

- Deleting a black node may cause a path to have fewer black nodes than other paths, violating the property that all paths from a node to its descendant leaves must have the same number of black nodes.
- Deleting a black node that has a red child may cause two red nodes to be adjacent, violating the property that red nodes cannot have red children.

To fix these (rebalancing the tree), we evaluate different cases:

1. **Sibling is red:** We recolor the sibling black, and its parent red, then rotate the parent towards the node we're deleting. **Converts into case 2, 3, or 4.**

2. **Sibling is black with two black children:** Recolor sibling red, and if the parent is red, recolor it black. If the parent is black, the black deficiency moves up to the parent, and we repeat the process from the parent.

3. **Sibling is black, sibling's near child is red, sibling's far child is black:** The deleted node (DN)'s "near child" is the child of the sibling that is closer to the deleted node. The DN's far child is the child of the sibling that is farther from the deleted node. 

```     
           P
       /      \
    DN        S
           /       \
       near (R)  far (B)
```

In this case, we recolor the near child black, and the sibling red, then rotate the sibling away from the deleted node. **This transforms the situation into case 4.**

4. **Sibling is black, sibling's far child is red:** Recolor the sibling to the parent's color, recolor the parent to black, recolor the far child to black, and rotate the parent towards the double black node.

## Code & Visualization

I created an interactive visualization with Gemini CLI, using React, Tailwind CSS, Framer, and TypeScript. Try it here: https://red-black-visualizer.pages.dev/