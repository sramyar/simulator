#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <unistd.h> 
#include <signal.h>

#include"Queue.c"

#define FIRST_TEST Empty_queue
#define MAXSCORE 60

static uint8_t testsPassed;

int testStatus;


enum Test_enumerator {
    Empty_queue = 0,
    Enqueue_test,
    Dequeue_test,
    
    NUM_TESTS,
};

char* testName(int test)
{
    switch (test)
    {
    case Empty_queue:
        return "Empty_queue";

    case Enqueue_test:
        return "Enqueue_test";
    
    case Dequeue_test:
        return "Dequeue_test";
    }

    return "";
}

uint8_t runTest(Queue* q, int test)
{
    int x = -1; // reserved for dequeue return value;
    switch (test)
    {
    case Empty_queue:
        if (count(q) != 0) return 1;
        return 0;
    
    case Enqueue_test:
        enqueue(q,1);
        if (count(q) != 1) return 1;

        enqueue(q,2);
        enqueue(q,3);
        if (count(q) != 3) return 2;
        return 0;
    
    case Dequeue_test:
        enqueue(q,1);
        enqueue(q,2);
        enqueue(q,3);
        x = dequeue(q);
        if (x != 1 || count(q) != 2) return 1;

        enqueue(q,4);
        x = dequeue(q);
        if (x != 2 || count(q) != 2) return 2;

        enqueue(q,5);
        x = dequeue(q);
        if (x != 3 || count(q) != 2) return 3;

        enqueue(q,6);
        x = dequeue(q);
        if (x != 4 || count(q) != 2) return 4;

        x = dequeue(q);
        if (x != 5 || count(q) != 1) return 5;

        x = dequeue(q);
        if (x != 6 || count(q) != 0) return 6;

        return 0;    
    
    }

    return 255; //for when things go wrong
}


int main(void)
{
    testsPassed = 0;
    int arr[4];
    for (uint8_t i = FIRST_TEST; i <  NUM_TESTS; i++){
        Queue* q = initializeQueue(4, arr);
        testStatus = runTest(q,i);
        destructQueue(q);
        if (testStatus == 0) testsPassed++;
    }

    uint8_t totalScore = testsPassed*20;

    printf("\nYou will receive %d out of %d possible points on the unit tests\n\n",totalScore, MAXSCORE);
    exit(0);
    return 0;
}