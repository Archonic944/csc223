#include "SORT.H"
#include "BDSCTEST.H"
#define TRUE 1
#define FALSE 0

int sorted(arr, n)
int arr[];
int n;
{
  int i, prev;
  prev = arr[0];
  for (i = 1; i < n; i++)
    if (arr[i] < prev)
      return FALSE;
    else
      prev = arr[i];
  return TRUE;
}

int is_heap(arr, i, size)
int arr[];
int i, size;
{
  int lchild, rchild;
  lchild = 2 * i + 1;
  rchild = 2 * i + 2;
  if (lchild >= size) return TRUE; /* It's a leaf node */
  if (rchild >= size) return arr[i] >= arr[lchild]; /* Only has left child */
  if ((arr[i] < arr[lchild]) || (arr[i] < arr[rchild])) return FALSE;
  return is_heap(arr, lchild, size) && is_heap(arr, rchild, size);
}


int is_bst_util(node, min, max)
struct TsNode *node;
int min, max;
{
  if (node == NULL) return TRUE;
  if (node->ts_val < min || node->ts_val > max) return FALSE;
  return is_bst_util(node->ts_left, min, node->ts_val) &&
         is_bst_util(node->ts_right, node->ts_val, max);
}

int is_bst(node)
struct TsNode *node;
{
  return is_bst_util(node, -32767, 32767);
}

main()
{
  int a[16];
  int b[7];
  int c[9];
  TEST_CASE("Bubble Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    bubble_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  TEST_CASE("Insertion Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    insertion_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  TEST_CASE("Selection Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    selection_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  TEST_CASE("Merge Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    merge_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  TEST_CASE("Quick Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    quick_sort(a, 16);
    ASSERT(sorted(a));
  }
  /*
  TEST_CASE("Radix Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    radix_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  */
  TEST_CASE("Test is_heap") {
    initw(b, "13, 8, 11, 4, 2, 7, 9");
    ASSERT(is_heap(b, 0, 7));
    initw(b, "8, 13, 11, 4, 2, 7, 9");
    ASSERT(!is_heap(b, 0, 7));
    initw(a, "42, 30, 36, 20, 8, 17, 12, 3, 9, 6, 7, 13, 5, 4, 11, 2");
    ASSERT(is_heap(a, 0, 16));
    initw(c, "13, 8, 11, 4, 2, 7, 9, 12, 42");
    ASSERT(is_heap(c, 0, 7));
    ASSERT(!is_heap(c, 0, 8));
  }
  TEST_CASE("Test reheap_up") {
    initw(c, "13, 8, 11, 4, 2, 7, 9, 12, 42");
    ASSERT(!is_heap(c, 0, 8));
    reheap_up(c, 8);
    ASSERT(is_heap(c, 0, 8));
    ASSERT(!is_heap(c, 0, 9));
    reheap_up(c, 9);
    ASSERT(is_heap(c, 0, 9));
  }
  TEST_CASE("Test heapify") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    ASSERT(!is_heap(a, 0, 16));
    heapify(a, 16);
    ASSERT(is_heap(a, 0, 16));
    initw(c, "42, 13, 8, 11, 4, 2, 7, 9, 12");
    heapify(c, 9);
    ASSERT(is_heap(c, 0, 9));
  }
  TEST_CASE("Test reheap_down") {
    initw(a, "42, 30, 36, 20, 8, 17, 12, 3, 9, 6, 7, 13, 5, 4, 11, 2");
    ASSERT(is_heap(a, 0, 16));
    swap(&a[0], &a[15]);
    ASSERT(!is_heap(a, 0, 16));
    reheap_down(a, 15);
    ASSERT(is_heap(a, 0, 15));
    swap(&a[0], &a[14]);
    reheap_down(a, 14);
    ASSERT(is_heap(a, 0, 14));
  }
  TEST_CASE("Heap Sort") {
    initw(b, "1, 2, 3, 4, 5, 6, 7");
    heap_sort(b, 7);
    ASSERT(sorted(b, 7));
    initw(c, "42, 13, 8, 11, 4, 2, 7, 9, 12");
    heap_sort(c, 9);
    ASSERT(sorted(c, 9));
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    heap_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  /*
  TEST_CASE("Shell Sort") {
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    shell_sort(a, 16);
    ASSERT(sorted(a, 16));
  }
  */

  TEST_CASE("Tree Sort") {
    struct TsNode *tsRoot;
    int i;
    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    
    tsRoot = NULL;
    for (i = 0; i < 16; i++)
        ts_insert(&tsRoot, a[i]);
    ASSERT(is_bst(tsRoot));
    ts_free(tsRoot);

    initw(a, "31, 4, 15, 9, 26, 5, 35, 8, 97, 23, 84, 62, 64, 38, 35, 27");
    tree_sort(a, 16);
    ASSERT(sorted(a, 16));
  }

}
