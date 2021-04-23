#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h> 

#include"Queue.c"

#define FIRST_TEST Empty_queue
#define MAXSCORE 60

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;


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


void segfault_handler(int signal) { // everyone knows what this is
  testStatus = 255;
  longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
  if (disable_exit_handler) return; // allow this to be disabled
  testStatus = 255;
  longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
  testStatus = 255;
  longjmp(test_crash, 3);
}

int main(int argc, char **argv)
{
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./queue_test"));
    exit(1);
    }

    printf("\n"); // more spacing
    if (argc == 2) printf("\n"); // consistency in verbose mode

    testsPassed = 0;
    disable_exit_handler = 0;
    atexit(exit_attempt_handler);
    signal(SIGSEGV, segfault_handler);

    int arr[4]; // initializing array used for implementing queue
    for (uint8_t i = FIRST_TEST; i <  NUM_TESTS; i++){
        Queue* q = initializeQueue(4, arr);
        testStatus = runTest(q,i);
        destructQueue(q);

        uint8_t fail_type = setjmp(test_crash);
        if (argc == 2) { // it's verbose mode
            printf("Test %s: %s", testName(i), testStatus == 0 ? "PASSED" : "FAILED");
            if (testStatus == 255) {
                printf(": due to a %s\n", fail_type == 1 ? "segfault" : fail_type == 2 ? "program exit" : "program interruption");
                printf("\nWARNING: Program will now stop running tests\n\n");
            break;
            } else if (testStatus != 0) {
                printf(": test %d\n", testStatus);
            } else {
                printf("\n");
                }
        }

        if (testStatus == 0) testsPassed++;
    }

    disable_exit_handler = 1;

    uint8_t totalScore = testsPassed*20;

    if (argc == 2 ) printf("\nYou passed %d out of %d tests\n", testsPassed,
      NUM_TESTS);

    else if (testStatus == 255) {
        if (totalScore < 10) {totalScore = 10;}
        //totalScore = 10; // charity points
        if (argc == 2) printf("Receiving charity points because your program crashes\n");
    }

    printf("\nYou will receive %d out of %d possible points on the unit tests\n\n",totalScore, MAXSCORE);
    exit(0);
    return 0;
}