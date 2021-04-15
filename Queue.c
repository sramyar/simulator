#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
// Implemeting Queue

// Signature
typedef struct Queue{int head; int tail; int length; int count; int* array;} Queue;


// Initializing Queue
Queue* initializeQueue(int n, int* arr)
{
    Queue* q = malloc(sizeof(Queue));
    q->array = arr;
    q->length = n;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    return q;
}

void destructQueue(Queue* q)
{
    free(q);
    q = NULL;
}


void enqueue(Queue* q, int x)
{
    assert(q->count < q->length - 1);
    (q->array)[q->tail] = x;
    if (q->tail == (q->length) - 1){
        q->tail = 0;
    }
    else{
        (q->tail)++;
    }
    (q->count)++;
}

int dequeue(Queue* q)
{
    assert(q->count > 0);
    int x = q->array[q->head];
    if (q->head == (q->length) - 1){
        (q->head) = 0;
    }
    else{
        (q->head)++;
    }
    (q->count)--;
    return x;
}

void printQueue(Queue* q)
{
    if(q->count == 0){printf("[ ]\n");}
    int cue = q->head;
    if(q->head < q->tail){
        while (cue < (q->tail))
        {
            printf("%d <-- ",q->array[cue]);
            cue++;
        }
        
    }
    else{
        for(int i=0; i < q->count ; i++){
            printf("%d <-- ", q->array[cue]);
            if(cue != q->length - 1){cue++;}
            else {cue = 0;}
        }
    }
    printf("\n");
}


int count(Queue* q)
{
    return q->count;
}
