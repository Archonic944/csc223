# QuickSort Algorithm

## How QuickSort Works
QuickSort is a highly efficient, in-place sorting algorithm that uses a divide-and-conquer strategy. It operates in three concise steps:

1. **Choose a Pivot**: Select a benchmark element from the array. A common approach to optimize performance is the "Median-of-Three" method, which picks the median of the first, middle, and last elements to avoid worst-case scenarios.
2. **Partition the Array**: Rearrange the array elements so that all items smaller than the pivot are moved to its left, and all items larger are moved to its right. The pivot is then placed in its final, guaranteed sorted position.
3. **Recurse**: Recursively apply the same pivot selection and partitioning steps to the remaining unsorted sub-arrays on the left and right of the pivot until the entire array is fully sorted.

---

## Code Implementation

### Median of Three
```c
int* medianOfThree(startp, endp)
int* startp;
int* endp;
{
    /* Calculate midp, then find the median of start, mid, and end */
    if((startn < endn && startn > midn) || (startn < midn && startn > endn)) return startp;
    else if((endn < startn && endn > midn) || (endn < midn && endn > startn)) return endp;
    return midp;
}
```

### Partitioning
```c
int* partition(startp, endp, pivot)
{
    swap(pivot, endp); /* Move pivot to the end temporarily */
    while(1){
        s = itmLeft(s, e, p);   /* Find item > pivot */
        e = itmRight(s, e, p);  /* Find item < pivot */
        if(s >= e || s == NULL || e == NULL) break;
        swap(s, e); /* Swap out-of-place elements */
    }
    swap(endp, s); /* Move pivot into its final resting spot */
    return s;
}
```

### Recursive Sorting
```c
void qsortRec(startp, endp)
{
    /* Handle base cases */
    
    pivot = medianOfThree(startp, endp);
    pivot = partition(startp, endp, pivot);
    
    qsortRec(startp, pivot-1);   /* Sort Left Side */
    qsortRec(pivot+1, endp);     /* Sort Right Side */
}
```

## A Nice Visualizer

From Virginia Tech's CS department: https://opendsa-server.cs.vt.edu/embed/quicksortAV

Enter space separated values and click "run".