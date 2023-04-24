#include <stdio.h>
#include <assert.h>
#include "delivery.h"
#include "mapping.h"

void valid_input() {
    printf("----- TESTING WITH VALID INPUTS -----\n");

    struct Package shipment = { 0 };
    strcpy(shipment.input, "20 0.5 12L");
    struct Map map = { 0 };

    assert(assignInputs(&shipment), 1);
    assert(validateInputs(&shipment), 1);
    //assert(strcmp(processShipment(&shipment, &map), "BLUE") == 0);

   Result result = processShipment(&shipment, &map);
    //assert(strcmp(result.route_color, "BLUE") == 0);
    //assert(strcmp(result.divert_message, "no diversion") == 0);

    printf("----- TESTING WITH VALID INPUTS PASSED -----\n");
     
}

void invalid_input() {
    struct Package shipment = { 0 };
    struct Map map = { 0 };
    int result = 0;

    display();
    strcpy(shipment.input, "abc");
    result = readInput(&shipment);
    while (result == 0) {
        processShipment(&shipment, &map);
        result = readInput(&shipment);
    }
}

void valid_input_blue_route() {
    struct Map map = { 0 };
    populateMap(&map);

    struct Package shipment = { 0 };
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
    /*invalid_input();*/

    //valid_input_blue_route();

    printf("All tests passed!\n");

    return 0;
}
