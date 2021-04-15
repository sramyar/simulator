#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"

// returns largest element in heap/highest priority
int get_max(Heap* h)
{
    return h->array[0];
}

// extract max element in heap
int extract_max(Heap* h)
{
    assert(h->size > 0);
    int max = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size --;
    heapify(h, 0);
    return max;
}

// increase priority/value of element i in the heap to new_value
void increase_priority(Heap* h, int i, int new_value)
{
    assert(h->array[i] <= new_value);
    h->array[i] = new_value;
    while (i > 0 && h->array[parent(i)] < h->array[i])
    {
        swap(h->array, i, parent(i));
        i = parent(i);
    }
    
}

// insert value/key to heap
void insert(Heap* h, int value)
{
    // *** NOTE: changed the initialization both here for arr[size-1] and also
    // the main array for heap in main() ***
    assert(h->length > h->size);
    h->size++;
    h->array[h->size - 1] = -2;
    increase_priority(h, h->size - 1, value);
}

