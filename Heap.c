// Implementation of (Max) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"

// Helper funcs for fetching parent and left/right child
int parent(int i)
{
    return (i-1)/2;
}

int left(int i)
{
    return 2*i+1;
}

int right(int i)
{
    return 2*i + 2;
}

// Helper for replacing A[i] and A[j] elements in an array
void swap(int* A, int i, int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

// Helper for printing an array
void printArray(int* A, int size)
{
    printf("[ ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d, ",A[i]);
    }
    printf(" ]\n");
    
}

// declare Heap struct
typedef struct Heap {int length; int size; int* array;} Heap;


Heap* initializeHeap(int len, int h_size, int* arr)
{
    Heap* h = malloc(sizeof(Heap));
    h->array = arr;
    h->size = h_size;
    h->length = len;
    return h;
}


// Heap destructor

void destructHeap(Heap* h)
{
    free(h);
    h = NULL;
}


// Maintain Heap property given an index i for heal A
void heapify(Heap* h, int i)
{
    int largest;
    int l = left(i);
    int r = right(i);
    if (l < h->size && h->array[l] > h->array[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r < h->size && h->array[r] > h->array[largest]){
        largest = r;
    }
    if (largest != i){
        swap(h->array, i, largest);
        heapify(h, largest);
    }
}

// Build heap
Heap* array_to_Heap(int* A, int len, int size)
{
    //initializeHeap(h, len, size, A);
    Heap* h = initializeHeap(len,size,A);
    for (int i = h->length/2 ; i >= 0; i--){
        heapify(h,i);
    }
    return h;
}

int size(Heap* h)
{
    return h->size;
}

int len(Heap* h)
{
    return h->length;
}

