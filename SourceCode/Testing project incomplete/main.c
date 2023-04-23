#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "delivery.h"
#include "mapping.h"

int main() {
    struct Package* shipment = malloc(sizeof(struct Package));
    //  struct package* storage = malloc(sizeof(struct Package));
    struct Truck truckG = { MAX_WEIGHT, MAX_SIZE, 0, 0, 0, 0 };
    struct Truck truckB = { MAX_WEIGHT, MAX_SIZE, 0, 0, 0, 0 };
    struct Truck truckY = { MAX_WEIGHT, MAX_SIZE, 0, 0, 0, 0 };
    struct Truck trucks[3];
    struct Storage storage = { 0 };
    trucks[0] = truckG; //Hopefully this works
    trucks[1] = truckB;
    trucks[2] = truckY;


    struct Map map = populateMap();

    int quit = 0;

    if (shipment == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }

    display();

    while (!quit) {
        printf("\nEnter shipment weight in kg, box size and destination (0 0 x to stop): ");
        quit = readInput(shipment);

        if (!quit) {
           processShipment(shipment, map, trucks, storage);
            
        }
    }

    printf("Thanks for shipping with Seneca!\n");
   // struct Map routeMap = addRoute(&map, &blueRoute);
    printMap(&map, 1, 1);
    free(shipment);
    return 0;
}
