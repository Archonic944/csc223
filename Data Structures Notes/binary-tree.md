# Binary Tree Notes

## Definition

A tree is a hirearchical graph in which each node has at most two children, referred to as the left child and the right child. 

## Vocab

**Root node**: The topmost node.

**Leaf node**: A node with no children.

**Path**: A sequence of nodes and edges connecting a node with another node. On a tree, there is only one path between any two nodes.

**Ancestor node**: Any predecessor of a node on the path from root to that node.

**Descendant node**: Any successor of a node on the path from that node to a leaf.

**Level number**: Each child's level number is one more than its parent's level number. The root node is at level 0.

**Degree**: The number of children of a node. A leaf node has degree 0. In-degree and out-degree follow logically.

## General Trees

A general tree stores elements hirearchically. Each node can have an arbitrary number of children. We often lose a lot of performance benefit when using general trees because of the arbitrary amount of children. Because of that, we like to convert things to binary trees. Full conversion is not always possible.

## Forests

A forest is a disjoint set of trees. You can get a forest by deleting the root and the edges from the root to its children. You can also convert a forest to a tree by creating a new root and connecting it to the roots of the trees in the forest.

## Binary Trees

Binary trees are a special type of tree where each node has at most two children. 

A binary tree with only a root node has height 1. A binary tree of height h has at most $2^{h} - 1$ nodes, and at least h nodes.

Two binary trees are "similar" if they have the same structure, and are "copies" if they have the same structure and the same node values.

Two nodes are "siblings" if they have the same parent and have the same level number.

### Complete Binary Trees

A binary tree is complete if every level satisfies two properties:

1. Every level, except the possibly the last, is completely filled.
2. All nodes are as far left as possible.

![a complete binary tree](image.png)

### Extended Binary Trees

In an extended binary tree, every node has either 0 or 2 children. Nodes having two children are called internal nodes, and nodes having no children are called external nodes. We can convert any binary tree to an extended binary tree by adding external nodes as children of internal nodes that have only one child.

### Binary Trees in Memory

1. Linked: The simplest method. Each node has a pointer to its left child, a pointer to its right child, and a data value. Every tree has a pointer `ROOT`, and if `ROOT` is null, then the tree is empty.
2. Sequential: Uses a one-dimensional array. The simplest technique, but inefficient.
A one-dimensional array called `TREE` stores the tree elements:
- Root is stored at `TREE[1]`
- Children of node at location `K` are stored at `TREE[2*K]` (left) and `TREE[2*K+1]` (right)
- Maximum array size is `2^h - 1`, where `h` is the tree height
- `NULL` represents empty nodes or subtrees; `TREE[1] = NULL` means the tree is empty

### Binary Search Trees

A binary search tree (or "ordered binary tree") has every node arranged in order. Every value on the left subtree of a node is less than the node's value, and every value on the right subtree is greater than the node's value.

So, when we search for elements, 

### Expression Trees

Binary trees are sometimes used to store algebraic expressions. For example: ![((a + b) – (c * d)) % ((e^f) / (g – h))](image-1.png)

### Traversing a Binary Tree

Binary trees can be traversed in many different ways:

1. Pre-order Traversal: Visit the root, traverse the left subtree, traverse the right subtree. Also known as the "node-left-right" traversal. In this method, the entire left subtree of the root is visited before any node in the right subtree is visited.
2. In-order Traversal: Traverse the left subtree, visit the root, traverse the right subtree. Often used to display the elements of a binary tree. In this method, the first node visited is the leftmost node in the tree. The traversal then works its way up, visiting each node only after its entire left subtree has been processed.

![IN-ORDER TRAVERSAL ORDER: G, D, H, L, B, E, A, C, I, F, K, and J](image-2.png)

A key point of confusion: "left-node-right" does not mean we finish the entire left half of the tree before visiting any node on the right. The rule applies **recursively at every node**. So when we arrive at a node like C (which has no left child), we visit it immediately — even if C sits above nodes like I, J, and K that are deeper in the tree. C's position as a right child of A does not delay its visit; what matters is that C itself has no left subtree to process first.

3. Post-order traversal: Traverse the left subtree, traverse the right subtree, visit the root. Also known as the "left-right-node" traversal. Can be used to extract postfix notation from an expression tree.

4. Level-order traversal: Visit the nodes by level, also known as a breadth-first traversal.

