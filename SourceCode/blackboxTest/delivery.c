#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "delivery.h"
#include "mapping.h"
#include <string.h>

void display() {
    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n\n");
}

int readInput(struct Package* shipment) {
    fgets(shipment->input, sizeof(shipment->input), stdin);

    if (strcmp(shipment->input, "0 0 x\n") == 0) {
        return 1;
    }
    else if (sscanf(shipment->input, "%lf %lf %d %c", &shipment->weight, &shipment->size, &shipment->row, &shipment->column) != 4) {
        printf("Invalid input\n");
        return 0;
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
    return (row >= 0 && row < MAP_ROWS&& isalpha(column) && toupper(column) >= 'A' && toupper(column) <= 'Y');
}


int charToInt(char c) {
    int returnC = 0;
    char chara;
    //convert upper to low
    if (c >= 'A' && c <= 'Z') {
        chara = c + 32;
    }
    if (c >= 'a' && c <= 'z') {
        returnC = c - 'a';
    }
    return returnC;
}
char intToChar(int in) {
    char chara = 'A' + in;
    return chara;
}
void processShipment(struct Package* shipment, struct Map* map) {
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
    struct Route blueRoute = getBlueRoute();
    struct Route greenRoute = getGreenRoute();
    struct Route yellowRoute = getYellowRoute();

    int blueClosestIdx = getClosestPoint(&blueRoute, destination);
    int greenClosestIdx = getClosestPoint(&greenRoute, destination);
    int yellowClosestIdx = getClosestPoint(&yellowRoute, destination);

    double blueDist = distance(&destination, &blueRoute.points[blueClosestIdx]);
    double greenDist = distance(&destination, &greenRoute.points[greenClosestIdx]);
    double yellowDist = distance(&destination, &yellowRoute.points[yellowClosestIdx]);

    const char* divertMessage = NULL;
    const char* routeColor = NULL;
    struct Route* selectedRoute = NULL;
    int closestIdx = -1;

    struct Point origin = { 0, -1 };
    struct Point dest = { destination.col, destination.row };
    struct Route directRoute = shortestPath((const struct Map*)&map, origin, dest);
    int pass = 0;
    /*  Direct route is the route from 0,0 to the destination.
    */
    // for (int x = 0; x < directRoute.numPoints; x++) { //Could implement a new way to find the closest route but this is probably sufficient.
     //    printf("%d, %d \n", directRoute.points[x].col, directRoute.points[x].row);
 //        if (directRoute.points[x].col == blueRoute.points);
    // }


     //Added the points from direct route to which route is most efficient; Haven't figured how to add the route message.
    if (blueDist <= greenDist && blueDist <= yellowDist) {
        routeColor = "BLUE";

        for (int x = 0; x < directRoute.numPoints; x++) {   //nested for loop to check if the point is already apart of the route to prevent duplicates
            for (int y = 0; y < blueRoute.numPoints; y++) {
                if (blueRoute.points[y].col == directRoute.points[x].col && blueRoute.points[y].row == directRoute.points[x].col) {
                    pass = 1;
                }
            }
            if (pass == 0) {
                addPtToRoute(&blueRoute, directRoute.points[x]);
            }

            pass = 0;
        }

        selectedRoute = &blueRoute;
        closestIdx = blueClosestIdx;
        divertMessage = (blueDist <= 1.0) ? "no diversion" : "divert:";
    }
    else if (greenDist <= blueDist && greenDist <= yellowDist) {
        routeColor = "GREEN";

        for (int x = 0; x < directRoute.numPoints; x++) {   //nested for loop to check if the point is already apart of the route to prevent duplicates
            for (int y = 0; y < greenRoute.numPoints; y++) {
                if (greenRoute.points[y].col == directRoute.points[x].col && greenRoute.points[y].row == directRoute.points[x].col) {
                    pass = 1;
                }
            }
            if (pass == 0) {
                addPtToRoute(&greenRoute, directRoute.points[x]);
            }

            pass = 0;
        }

        selectedRoute = &greenRoute;
        closestIdx = greenClosestIdx;
        divertMessage = (greenDist <= 1.0) ? "no diversion" : "divert:";
    }
    else {
        routeColor = "YELLOW";

        for (int x = 0; x < directRoute.numPoints; x++) {   //nested for loop to check if the point is already apart of the route to prevent duplicates
            for (int y = 0; y < yellowRoute.numPoints; y++) {
                if (yellowRoute.points[y].col == directRoute.points[x].col && yellowRoute.points[y].row == directRoute.points[x].col) {
                    pass = 1;
                }
            }
            if (pass == 0) {
                addPtToRoute(&yellowRoute, directRoute.points[x]);
            }

            pass = 0;
        }

        selectedRoute = &yellowRoute;
        closestIdx = yellowClosestIdx;
        divertMessage = (yellowDist <= 1.0) ? "no diversion" : "divert:";
    }

    printf("Ship on %s LINE, %s\n", routeColor, divertMessage);

    struct Point startPoint;
    struct Point backPath = { -1, -1 }; // Initialize with invalid row and col values

    if (strcmp(divertMessage, "divert:") == 0) {
        if (routeColor == "BLUE") {
            startPoint = blueRoute.points[blueClosestIdx];
        }
        else if (routeColor == "GREEN") {
            startPoint = greenRoute.points[greenClosestIdx];
        }
        else {
            startPoint = yellowRoute.points[yellowClosestIdx];
        }

        struct Route possibleMoves = getPossibleMoves(&map, startPoint, backPath);

        // Print the possible moves
        for (int i = 0; i < possibleMoves.numPoints; i++) {
            printf("Move %d: (%d, %c)\n", i + 1, possibleMoves.points[i].row, possibleMoves.points[i].col + 'A');
        }
    }
    addRoute(&map, &blueRoute);
    addRoute(&map, &greenRoute);
    addRoute(&map, &yellowRoute);
}