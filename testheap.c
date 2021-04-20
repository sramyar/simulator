#include"PriorityQueue.c"



int main(void)
{
    int arr[10] = {16, 4 , 10, 14, 7, 9, 3, 2, 8, 1};

    Heap* h = initializeHeap(10, 10, arr);

    printf("\nprinting heap:\n");
    printArray(arr,h->size);

    heapify(h, 1);


    printf("\nprinting heap:\n");
    printArray(arr,h->size);

    // extract_max(h);
    // printf("\nprinting heap:\n");
    // printArray(arr,h->size);

    printf("\n -1/2 is %d\n", -1/2);

    return 0;

}