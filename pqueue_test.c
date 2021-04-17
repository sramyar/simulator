#include <stdint.h>
//#include"Heap.c"
#include"PriorityQueue.c"


#define FIRST_tEST Empty_heap
#define MAXSCORE 40

static uint8_t testsPassed;
int testStatus;

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


int main(void)
{
    testsPassed = 0;
    int arr[10];
    for (uint8_t i = 0; i < NUM_TESTS; i++){
        Heap* h = initializeHeap(10, 0, arr);
        testStatus = runTest(h, i);
        destructHeap(h);

        if (testStatus == 0) testsPassed++;
        else printf("\nFailed %s\n", testName(i));
    }

    uint8_t totalScore = testsPassed*8;

    printf("\nYou get %d out of %d for heap unit test\n", totalScore, MAXSCORE);
    exit(0);
    return 0;
}