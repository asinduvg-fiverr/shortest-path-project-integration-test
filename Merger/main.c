#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "delivery.h"
#include "mapping.h"

int main() {
    struct PackageNode* shipment = NULL;
    struct Truck truckG = { MAX_WEIGHT, MAX_SIZE, 0, 0 };
    struct Truck truckB = { MAX_WEIGHT, MAX_SIZE, 0, 0 };
    struct Truck truckY = { MAX_WEIGHT, MAX_SIZE, 0, 0 };
    struct Storage storage = { 0 };
    struct Map map = populateMap();
    int quit = 0;
    int numPackages = 0;

    display();

    while (!quit) {
        struct PackageNode* newNode = malloc(sizeof(struct PackageNode));
        if (newNode == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            return 1;
        }
        newNode->next = NULL;

        printf("Enter shipment weight in kg, box size and destination (0 0 x to stop): ");
        int readResult = readInput(&newNode->package);

        if (readResult == 1) {
            quit = 1;
            free(newNode);
        }
        else if (readResult == 0) {
            newNode->next = shipment;
            shipment = newNode;
            addPackageToTruck(&shipment->package, &truckG, &truckB, &truckY, map, &storage);
            numPackages++;
        }
    }

    printf("Thanks for shipping with Seneca!");

    // Free the shipment linked list
    struct PackageNode* current = shipment;
    while (current != NULL) {
        struct PackageNode* nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
