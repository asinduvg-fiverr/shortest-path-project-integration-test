#include <stdio.h>
#include <assert.h>
#include "mapping.h"
#include "simulator.h"

void test_validate_input()
{
    printf("----- TESTING WITH VALID INPUTS -----\n");

    Result result = { 0 };

    send("20 0.5 12L");
    result = receive();
    assert(result.routeColor == BLUE);
    assert(result.diversion == NO_DIVERSION);

    send("abc");
    result = receive();
    assert(result.routeColor == 0);

    send("1005 .5 12L");
    result = receive();
    assert(result.routeColor == 0);

    printf("----- TESTING WITH VALID INPUTS PASSED -----\n\n");  
}

void test_happy_path()
{
    printf("----- TESTING HAPPY PATH -----\n");

    Result result = { 0 };

    send("200 1.0 8Y");
    result = receive();
    assert(result.routeColor == GREEN);
    assert(result.diversion == DIVERT);

    send("500 1.0 8Y");
    result = receive();
    assert(result.routeColor == GREEN);
    assert(result.diversion == DIVERT);

    send("0 0 x");
    result = receive();
    assert(result.routeColor == 0);

    printf("----- TESTING HAPPY PATH PASSED -----\n\n");
}

int main() {

    test_validate_input();
    test_happy_path();

    printf("All tests passed!\n");

    return 0;
}
