#include <stdio.h>
#include <assert.h>
#include "mapping.h"
#include "simulator.h"

void valid_input()
{
    printf("----- TESTING WITH VALID INPUTS -----\n");

    send("20 0.5 12L");
    Result result = receive();
    assert(result.routeColor == BLUE);
    assert(result.diversion == NO_DIVERSION);

    printf("----- TESTING WITH VALID INPUTS PASSED -----\n\n");  
}

void _invalid_input_format()
{
    printf("\t---- TESTING WITH INVALID INPUT FORMAT ----\n");
    Package shipment = { 0 };
    strcpy(shipment.input, "abc");
    Map map = { 0 };

    assert(assignInputs(&shipment) == 0);
    printf("\t---- TESTING WITH VALID INPUT FORMAT PASSED ----\n");
}

void _invalid_input_weight()
{
    printf("\t---- TESTING WITH INVALID INPUT WEIGHT ----\n");
    Package shipment = { 0 };
    strcpy(shipment.input, "1005 .5 12L");
    Map map = { 0 };

    assert(assignInputs(&shipment) == 0);
    printf("\t---- TESTING WITH VALID INPUT FORMAT PASSED ----\n");
}

void invalid_input()
{
    printf("----- TESTING WITH INVALID INPUTS -----\n");

    _invalid_input_format();

    printf("----- TESTING WITH INVALID INPUTS PASSED -----\n\n");

}

void valid_input_blue_route() {
    Map map = { 0 };
    populateMap(&map);

    Package shipment = { 0 };
    shipment.weight = 20;
    shipment.size = 0.5;
    shipment.row = 12;
    shipment.column = 'L';

    /*const char* routeColor = processShipment(&shipment, &map);
    assert(strcmp(routeColor, "GREEN") == 0);*/
}



// Add more tests for other functions if necessary

int main() {
    /*test_readWeight();
    test_readSize();
    test_readDestination();*/
    // Add more test function calls if necessary

    valid_input();
    //invalid_input();

    //valid_input_blue_route();

    printf("All tests passed!\n");

    return 0;
}
