#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h> 

#include"PriorityQueue.c"


#define FIRST_tEST Empty_heap
#define MAXSCORE 40

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_enumerator{
    Empty_heap = 0,
    Get_Max,
    Extract_Max,
    Increase_Priority,
    Insert_Test,

    NUM_TESTS,
};

char* testName(int test)
{
    switch (test)
    {
    case Empty_heap:
        return "Empty_heap";

    case Get_Max:
        return "Get_Max";
    
    case Extract_Max:
        return "Extract_Max";
    
    case Increase_Priority:
        return "Increase_Priority";
    
    case Insert_Test:
        return "Insert_Test";
    }

    return "";
}

uint8_t runTest(Heap* h, int test)
{
    int x = -1; // reserved for extract max storage
    switch (test)
    {
    case Empty_heap:
        if (size(h) != 0) return 1;
        return 0;
    
    case Insert_Test:
        insert(h, 1);
        if (size(h) != 1 || get_max(h) != 1) return 1;
        
        insert(h, 2);
        if (size(h) != 2 || get_max(h) != 2) return 2;

        insert(h,10);
        if (size(h) != 3 || get_max(h) != 10) return 3;

        insert(h,5);
        if (size(h) != 4 || get_max(h) != 10) return 4;

        return 0;

    case Get_Max:
        insert(h, 100);
        if (size(h) != 1 || get_max(h) != 100) return 1;

        insert(h, 50);
        if (size(h) != 2 || get_max(h) != 100) return 2;

        insert(h, 1000);
        if (size(h) != 3 || get_max(h) != 1000) return 3;

        return 0;
    
    case Increase_Priority:
        insert(h, 2);
        insert(h, 3);
        insert(h, 50);
        insert(h, 12);
        increase_priority(h, 0, 500);
        if (size(h) != 4 || get_max(h) != 500) return 1;

        increase_priority(h, 1, 14);
        extract_max(h);
        if (size(h) != 3 || get_max(h) != 14) return 2;

        return 0;

    case Extract_Max:
        insert(h, 2);
        insert(h, 3);
        insert(h, 50);
        insert(h, 12);
        x = extract_max(h);
        if (size(h) != 3 || x != 50) return 1;

        insert(h, 15);
        x = extract_max(h);
        if (size(h) != 3 || x != 15) return 2;

        x = extract_max(h);
        if (size(h) != 2 || x != 12) return 3;

        return 0;
    }

    return 255;
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
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./pqueue_test"));
    exit(1);
    }

    printf("\n"); // more spacing
    if (argc == 2) printf("\n"); // consistency in verbose mode

    testsPassed = 0;
    disable_exit_handler = 0;
    atexit(exit_attempt_handler);
    signal(SIGSEGV, segfault_handler);

    int arr[10]; // initializing array for implementation of heap
    for (uint8_t i = 0; i < NUM_TESTS; i++){
        Heap* h = initializeHeap(10, 0, arr);
        testStatus = runTest(h, i);
        destructHeap(h);

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

    uint8_t totalScore = testsPassed*8;

    if (argc == 2 ) printf("\nYou passed %d out of %d tests\n", testsPassed,
      NUM_TESTS);

    else if (testStatus == 255) {
        if (totalScore < 10) {totalScore = 10;}
        //totalScore = 10; // charity points
        if (argc == 2) printf("Receiving charity points because your program crashes\n");
    }

    printf("\nYou get %d out of %d for heap unit test\n", totalScore, MAXSCORE);
    exit(0);
    return 0;
}