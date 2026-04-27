#ifndef SORT_H
#define SORT_H

#define NULL 0
#define TRUE 1
#define FALSE 0
#define MAXNUMS 500
#define BASE 10
#define MAXDIGITS 5
#define MAXSIZE 256

/* ==============UTILITIES==============*/

void swap(a, b)
int *a;
int *b;
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

/* =============BUBBLE SORT=============*/

bubble_sort(arr, n)
int arr[];
int n;
{
  int i, j;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j+1])
      {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}

/* ===========INSERTION SORT============*/

insertion_sort(arr, n)
int arr[];
int n;
{
  int i, j, temp;
  for (i = 1; i < n; i++)
  {
    temp = arr[i];
    j = i - 1;
    while((j >= 0) && (temp < arr[j]))
    {
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = temp;
  }
}

/* ===========SELECTION SORT============*/

int smallest(arr, k, n)
int arr[];
int k, n;
{
  int pos, small, i;
  pos = k;
  small = arr[k];
  for (i = k + 1; i < n; i++) {
    if (arr[i] < small) {
      small = arr[i];
      pos = i;
    }
  }
  return pos;
}

selection_sort(arr, n)
int arr[];
int n;
{
  int k, pos;
  for (k = 0; k < n; k++) {
    pos = smallest(arr, k, n);
    swap(&arr[k], &arr[pos]);
  }
}

/* ==============MERGE SORT==============*/

merge(arr, b, m, e)
int arr[];
int b, m, e;
{
  int i, j, k, s;
  int temp[MAXSIZE];

  i = b;
  j = m + 1;
  k = 0;
  s = e - b;

  while (i <= m && j <= e)
    temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
  if (i > m)
    while (j <= e)
      temp[k++] = arr[j++];
  else
    while (i <= m)
      temp[k++] = arr[i++];
  for (k = 0; k <= s; k++)
    arr[k+b] = temp[k];
}

msort(arr, left, right)
int arr[];
int left, right;
{
  int mid;
  if (left < right)
  {
    mid = left + (right - left) / 2;
    msort(arr, left, mid);
    msort(arr, mid+1, right);
    merge(arr, left, mid, right);
  }
}

merge_sort(arr, n)
int arr[];
int n;
{
  if (n <= 0) return;
  msort(arr, 0, n-1);
}

/* ==============QUICK SORT==============*/

int partition(arr, b, e)
int arr[];
int b, e;
{
  int l, r, temp, loc, flag;
  loc = l = b;
  r = e;
  flag = FALSE;

  while (flag != TRUE) {
    while ((arr[loc] <= arr[r]) && (loc != r)) r--;
    if (loc == r)
      flag = TRUE;
    else
      if (arr[loc] > arr[r]) {
        swap(&arr[loc], &arr[r]);
        loc = r;
      }
    if (flag != TRUE) {
      while ((arr[loc] >= arr[l]) && (loc != l)) l++;
      if (loc == l)
        flag = TRUE;
      else
        if (arr[loc] < arr[l]) {
          swap(&arr[loc], &arr[l]);
          loc = l;
        }
    }
  }
  return loc;
}

qsort(arr, b, e)
int arr[];
int b, e;
{
  int loc;
  if (b < e) {
    loc = partition(arr, b, e);
    qsort(arr, b, loc-1);
    qsort(arr, loc+1, e);
  }
}

void quick_sort(arr, n)
int arr[];
int n;
{
  qsort(arr, 0, n-1);
}

/* ==============RADIX SORT==============*/

/*
counting_sort(arr, tmp, cnt, n, pos)
int arr[];
int tmp[];
int cnt[];
int n;
int pos;
{
  int i;
  int d;
  int base;

  base = 1;
  for (i = 0; i < pos; i++)
    base *= BASE;

  for (i = 0; i < BASE; i++)
    cnt[i] = 0;
  for (i = 0; i < n; i++) {
    d = (arr[i] / base) % BASE;
    cnt[d]++;
  }

  for (i = 1; i < BASE; i++)
    cnt[i] += cnt[i - 1];

  for (i = n - 1; i >= 0; i--) {
    d = (arr[i] / base) % BASE;
    cnt[d]--;
    tmp[cnt[d]] = arr[i];
  }
  for (i = 0; i < n; i++)
    arr[i] = tmp[i];
}

radix_sort(arr, n)
int arr[];
int n;
{
  int tmp[MAXNUMS];
  int cnt[BASE];
  int pass;
  for (pass = 0; pass < MAXDIGITS; pass++)
    counting_sort(arr, tmp, cnt, n, pass);
}
*/

/* ==============HEAP SORT==============*/

reheap_up(heap, n)
int heap[];
int n;
{
  int i, val;
  i = n - 1;
  val = heap[i];
  while ((i > 0) && (heap[i/2] < val)) {
    heap[i] = heap[i/2];
    i /= 2;
  }
  heap[i] = val;
}

reheap_down(heap, n)
int heap[];
int n;
{
  int i, child, left, right;
  i = 0;
  while (TRUE) {
    left = 2 * i + 1;
    if (left >= n) return;             /* heap[i] is a leaf node */
    right = left + 1;
    child = left;
    if (right < n && heap[right] > heap[left])
      child = right;
    if (heap[i] >= heap[child]) return; /* It's now a heap */
    swap(&heap[i], &heap[child]);
    i = child;
  }
}

heapify(arr, n)
int arr[];
int n;
{
  int i;
  for (i = 1; i <= n; i++) {
    reheap_up(arr, i);
  }
}

heap_sort(arr, n)
int arr[];
int n;
{
  int e, i;
  heapify(arr, n);
  for (e = n - 1; e > 1; e--) {
    swap(&arr[0], &arr[e]);
    reheap_down(arr, e-1);
  }
}

/* ==============SHELL SORT==============*/

/*
int CIURA[9];

shell_sort(arr, n)
int arr[];
int n;
{
  int i, a, b, h, temp;

  CIURA[0] = 1750; CIURA[1] = 701; CIURA[2] = 301; CIURA[3] = 132;
  CIURA[4] = 57;   CIURA[5] = 23;  CIURA[6] = 10;  CIURA[7] = 4;
  CIURA[8] = 1;

  for (i = 0; i < 9; i++) {
    h = CIURA[i];
    if (h >= n)
      continue;

    for (a = h; a < n; a++) {
      temp = arr[a];
      b = a;
      while (b >= h && arr[b - h] > temp) {
        arr[b] = arr[b - h];
        b = b - h;
      }
      arr[b] = temp;
    }
  }
}
*/

/* ==============TREE SORT==============*/

struct TsNode {
    int           ts_val;
    struct TsNode *ts_left;
    struct TsNode *ts_right;
};

ts_insert(nodePtr, n)
struct TsNode **nodePtr;
int n;
{
    struct TsNode *node;
    node = *nodePtr;
    if (node == NULL) {
        node = alloc(8);
        node->ts_val = n;
        node->ts_left  = NULL;
        node->ts_right = NULL;
        *nodePtr = node;
        return 0;
    }
    if (n < node->ts_val)
        ts_insert(&(node->ts_left),  n);
    else
        ts_insert(&(node->ts_right), n);
    return 0;
}

ts_inorder(node, out, countp)
struct TsNode *node;
int out[];
int *countp;
{
    if (node == NULL)
        return 0;
    ts_inorder(node->ts_left,  out, countp);
    out[*countp] = node->ts_val;
    (*countp)++;
    ts_inorder(node->ts_right, out, countp);
    return 0;
}

ts_free(node)
struct TsNode *node;
{
    if (node == NULL)
        return 0;
    ts_free(node->ts_left);
    ts_free(node->ts_right);
    free(node);
    return 0;
}

tree_sort(arr, n)
int arr[];
int n;
{
    int i, count;
    struct TsNode *tsRoot;

    tsRoot = NULL;
    for (i = 0; i < n; i++)
        ts_insert(&tsRoot, arr[i]);

    count = 0;
    ts_inorder(tsRoot, arr, &count);
    ts_free(tsRoot);

    return count;
}

#endif //SORT_H
