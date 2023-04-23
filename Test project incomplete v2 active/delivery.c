#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "delivery.h"
#include "mapping.h"
#include <string.h>
#include <float.h>

void display() {
    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n\n");
}

int readInput(struct Package* shipment) {
    int result = scanf("%lf %lf %d %c", &shipment->weight, &shipment->size, &shipment->row, &shipment->column);

    // Clear the input buffer
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

    if (result != 4) {
        return 1; // If the input is not in the expected format, return 1 to quit
    }

    if (shipment->weight == 0 && shipment->size == 0 && toupper(shipment->column) == 'X') {
        return 1; // If the user inputs "0 0 x", return 1 to quit
    }

    return 0;
}




int readWeight(double weight) {
    return (weight >= 1 && weight <= 1000);
}

int readSize(double size) {
    return (size == 0.25 || size == 0.5 || size == 1.0);
}


int readDestination(int row, char column) {
    return (row >= 0 && row < MAP_ROWS && isalpha(column) && toupper(column) >= 'A' && toupper(column) <= 'Y');
}

void addPackageToTruck(struct Package* shipment, struct Truck* truckG, struct Truck* truckB, struct Truck* truckY, struct Map map, struct Storage* storage) {

    struct Truck* trucks[] = { truckB, truckG, truckY };
    int num_trucks = 3;
    struct Route routes[] = { getBlueRoute(), getGreenRoute(), getYellowRoute() };
    char* colors[] = { "BLUE", "GREEN", "YELLOW" };
    int available[] = { 1, 1, 1 }; // 1 means the truck is available, 0 means it's not

    // Check if the package data is valid
    if (!readWeight(shipment->weight)) {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
        return;
    }

    if (!readSize(shipment->size)) {
        printf("Invalid size\n");
        return;
    }

    if (!readDestination(shipment->row, toupper(shipment->column))) {
        printf("Invalid destination\n");
        return;
    }

    struct Point destination = { shipment->row, toupper(shipment->column) - 'A' };

    int addedToTruck = 0;
    int availableTrucks = num_trucks;

    while (!addedToTruck && availableTrucks > 0) {
        int selectedIndex = -1;
        double minDistance = DBL_MAX;
        for (int i = 0; i < num_trucks; i++) {
            if (!available[i]) {
                continue;
            }

            struct Truck* truck = trucks[i];
            struct Route* route = &routes[i];
            int closestIdx = getClosestPoint(route, destination);
            double dist = distance(&destination, &route->points[closestIdx]);

            if (dist < minDistance) {
                selectedIndex = i;
                minDistance = dist;
            }
        }

        if (selectedIndex == -1) {
            printf("No suitable truck found. All trucks are full or unable to accommodate the package.\n");
            break;
        }

        struct Truck* selectedTruck = trucks[selectedIndex];
        if (selectedTruck->weight + shipment->weight <= selectedTruck->max_weight && selectedTruck->size + shipment->size <= selectedTruck->max_size) {
            // Process the shipment and add it to the truck if there is enough room
            processShipment(shipment, map, &routes[selectedIndex], colors[selectedIndex]);

            selectedTruck->weight += shipment->weight;
            selectedTruck->size += shipment->size;
            selectedTruck->row = shipment->row;
            selectedTruck->column = toupper(shipment->column);

            printf("Package added to %s truck\n", colors[selectedIndex]);
            addedToTruck = 1;
        }
        else {
            // Mark the truck as unavailable
            available[selectedIndex] = 0;
            availableTrucks--;

            if (availableTrucks == 0) {
                printf("No suitable truck found. All trucks are full or unable to accommodate the package.\n");
                addToStorage(shipment, storage);
            }
        }
    }
}
void addToStorage(struct Package* shipment, struct Storage* storage) {
    if (storage->numPackage >= 20) {
        printf("Storage is full. Package cannot be stored.\n");
        return;
    }

    storage->storage[storage->numPackage] = *shipment;
    storage->numPackage++;

    printf("Package added to storage. Ships Tomorrow\n");
}






void processShipment(struct Package* shipment, struct Map map, struct Route* selectedRoute, const char* routeColor) {
    // Check if weight is valid
    if (!readWeight(shipment->weight)) {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
        return;
    }

    // Check if size is valid
    if (!readSize(shipment->size)) {
        printf("Invalid size\n");
        return;
    }

    // Check if destination is valid
    if (!readDestination(shipment->row, toupper(shipment->column))) {
        printf("Invalid destination\n");
        return;
    }
    else if (toupper(shipment->column) > 'Y' || shipment->row > MAP_ROWS) {
        printf("Invalid destination\n");
        return;
    }

    // Calculate the closest route
    struct Point destination = { shipment->row, toupper(shipment->column) - 'A' };

    int closestIdx = getClosestPoint(selectedRoute, destination);
    double dist = distance(&destination, &selectedRoute->points[closestIdx]);

    const char* divertMessage = (dist <= 1.0) ? "no diversion" : "divert:";

    printf("Ship on %s LINE, %s\n", routeColor, divertMessage);

    struct Point startPoint;
    struct Point backPath = { -1, -1 }; // Initialize with invalid row and col values

    if (strcmp(divertMessage, "divert:") == 0) {
        startPoint = selectedRoute->points[closestIdx];
        struct Route possibleMoves = getPossibleMoves(&map, startPoint, backPath);

        // Print the possible moves
        for (int i = 0; i < possibleMoves.numPoints; i++) {
            printf("Move %d: (%d, %c)\n", i + 1, possibleMoves.points[i].row, possibleMoves.points[i].col + 'A');
        }
    }
}
