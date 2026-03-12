# Heap notes

A heap is a specialized tree. They are commonly used to implement priority queues, which is a queue that serves elements based on their order.

We will be discussing **binary heaps** in particular.

![A min heap and max heap](image-6.png)

## Min/Max heaps

In a **max heap**, every child of a node must be less than or equal to the node itself. This differs from a binary search tree, where the left child must be less than the node and the right child must be greater than the node. In a max heap, there is no such requirement for the left and right children.

In a **min heap**, every child of a node must be greater than or equal to the node itself. This is the opposite of a max heap.

## Array Backing

Elements of a **binary heap** are stored in an array. This is possible because a binary heap is a complete binary tree.

If an element is at position i, then its left child is at position 2i and its right child is at position 2i + 1. The parent of an element at position i is at position i/2.

The root of the heap is at index 0.

## Inserting Elements

Inserting elements are done in two steps:

1. Add the new value at the bottom of H (H is no longer a heap).
2. Let the new value rise to its appropriate place so that H is a heap again.

The second step is called **heapifying up**. To do it, we compare the new value with its parent. If they are not in the correct order, we swap the parent's value with the new value. We keep doing this up the tree.

## Removing Elements

We always remove (or "pop") the root of the heap. So, removing the top element is simple:

1. Replace the root node's value with the last element in the array.
2. Remove the last element from the array.
3. Let the new root value sink to its appropriate place so that the array represents a heap again.

The third step is called **heapifying down**. To do it, we compare the new root value with its children. If they are not in the correct order, we swap the root's value with the appropriate child's value. To determine which child to pick, we choose the larger one (in a max heap) or the smaller one (in a min heap). We keep doing this down the tree.

## Time Complexity

| Operation | Time Complexity |
| --- | --- |
| Get Min/Max | O(1) |
| Insert | O(log n) |
| Remove Min/Max | O(log n) |
| Heapify (Build Heap) | O(n) |
