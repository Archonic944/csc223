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

