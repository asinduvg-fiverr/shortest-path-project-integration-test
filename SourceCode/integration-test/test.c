#include <stdio.h>
#include <assert.h>
#include "delivery.h"
#include "mapping.h"

void valid_input() {
    struct Package shipment = { 0 };
    struct Map map = { 0 };
    int result = 0;

    display();
    result = readInput(&shipment);
    while (result == 0) {
        processShipment(&shipment, &map);
        result = readInput(&shipment);
    }

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

    const char* routeColor = processShipment(&shipment, &map);
    assert(strcmp(routeColor, "GREEN") == 0);
}



// Add more tests for other functions if necessary

int main() {
    /*test_readWeight();
    test_readSize();
    test_readDestination();*/
    // Add more test function calls if necessary

    /*valid_input();
    invalid_input();*/

    valid_input_blue_route();

    printf("All tests passed!\n");

    return 0;
}
