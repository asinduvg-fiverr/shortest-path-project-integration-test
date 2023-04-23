#include <stdio.h>
#include <assert.h>
#include "delivery.h"
#include "mapping.h"

void test_readWeight() {
    assert(readWeight(0) == 0);
    assert(readWeight(1) == 1);
    assert(readWeight(500) == 1);
    assert(readWeight(1000) == 1);
    assert(readWeight(1001) == 0);
}

void test_readSize() {
    assert(readSize(0.1) == 0);
    assert(readSize(0.25) == 1);
    assert(readSize(0.5) == 1);
    assert(readSize(1.0) == 1);
    assert(readSize(1.1) == 0);
}

void test_readDestination() {
    assert(readDestination(-1, 'A') == 0);
    assert(readDestination(0, 'A') == 1);
    assert(readDestination(0, 'Y') == 1);
    assert(readDestination(MAP_ROWS, 'Y') == 0);
    assert(readDestination(0, 'Z') == 0);
}



// Add more tests for other functions if necessary

int main() {
    test_readWeight();
    test_readSize();
    test_readDestination();
    // Add more test function calls if necessary

    printf("All tests passed!\n");

    return 0;
}
