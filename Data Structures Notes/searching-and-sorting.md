# Searching and Sorting Notes

## Introduction to Searching

Searching refers to finding the position of a particular value in a collection of values (like an array). 

- **Successful search**: The value is present in the array, and the process returns its location.
- **Unsuccessful search**: The value is not present, and the process typically returns a flag (like -1) or a message.

The algorithm chosen often depends on how the values are organized (e.g., whether the list is sorted or unordered).

### Linear Search
Also called sequential search. It is a simple method that checks every element of the array one by one in sequence until a match is found.

- **Use case**: Best for searching an unordered list of elements.
- **Complexity**: $O(n)$ where $n$ is the number of elements. The best case is 1 comparison (first element), and the worst case is $n$ comparisons (last element or not present). Performance can be slightly improved if the array is sorted, but it remains fundamentally $O(n)$.

### Binary Search
Works efficiently only on a **sorted** list. It follows a divide-and-conquer strategy, similar to looking up a word in a dictionary.

- **Mechanism**: 
  1. Calculate the middle index: `MID = (BEG + END) / 2`.
  2. Compare the search value (`VAL`) with the middle element.
  3. If `VAL == A[MID]`, the search is successful.
  4. If `VAL < A[MID]`, the value must be in the left half (`END = MID - 1`).
  5. If `VAL > A[MID]`, the value must be in the right half (`BEG = MID + 1`).
  6. Repeat until found or `BEG > END`.
- **Complexity**: $O(\log n)$. With each comparison, the search space is reduced by half.

### Interpolation Search
Also known as extrapolation search. Used on **sorted** arrays. It improves on binary search for uniformly distributed data by guessing the approximate location of the value, similar to how a human looks up a name in a phone book (e.g., looking for "Z" near the end, not the middle).

- **Mechanism**: Instead of dividing by 2, it calculates the probable position using:
  `MID = LOW + (HIGH - LOW) * ((VAL - A[LOW]) / (A[HIGH] - A[LOW]))`
- **Complexity**: Average case is $O(\log(\log n))$ for uniformly distributed elements. Worst case can degrade to $O(n)$ if elements increase exponentially.

### Jump Search
Also known as block search. Works on a **sorted** list. Instead of scanning all elements, it skips a fixed number of elements by jumping ahead. Once it finds an element greater than the desired value, it establishes a boundary and performs a linear search within that block.

- **Step Size**: Usually, the optimal jump step size ($k$) is calculated as $\sqrt{n}$.
- **Complexity**: $O(\sqrt{n})$.
- **Advantages**: 
  - Over Linear Search: Takes far fewer iterations for large lists.
  - Over Binary Search: When jumping backward is computationally expensive or slower than jumping forward, jump search is preferred because it only jumps backward once.
- **Optimizations**: Can be optimized by recursively applying jump search on the identified blocks instead of using linear search, pushing the complexity closer to logarithmic.