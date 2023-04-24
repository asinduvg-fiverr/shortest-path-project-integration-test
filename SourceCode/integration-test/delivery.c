#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "delivery.h"
#include <string.h>

void display() {
    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n\n");
}

int readInput(Package* shipment) {
    fgets(shipment->input, sizeof(shipment->input), stdin);

    return assignInputs(shipment);
}

int assignInputs(Package* shipment) {

    if (sscanf(shipment->input, "%lf %lf %d %c",
        &shipment->weight, &shipment->size, &shipment->row, &shipment->column) != 4) {
        printf("Invalid input\n");
        return 0;
    }
    return 1;
}

int validateInputs(Package* shipment) {
    // Check if weight is valid
    if (!readWeight(shipment->weight)) {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
        return 0;
    }

    // Check if size is valid
    if (!readSize(shipment->size)) {
        printf("Invalid size\n");
        return 0;
    }

    // Check if destination is valid
    if (!readDestination(shipment->row, toupper(shipment->column))) {
        printf("Invalid destination\n");
        return 0;
    }

    if (toupper(shipment->column) > 'Y' || shipment->row > MAP_ROWS) {
        printf("Invalid destination\n");
        return 0;
    }

    return 1;
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

void addPtToRouteWrapper(const Route * const direct_route, const Route * const route) {
    int pass = 0;
    for (int x = 0; x < direct_route->numPoints; x++) {   //nested for loop to check if the point is already a part of the route to prevent duplicates
        for (int y = 0; y < route->numPoints; y++) {
            if (route->points[y].col == direct_route->points[x].col && route->points[y].row == direct_route->points[x].col) {
                pass = 1;
            }
        }
        if (pass == 0) {
            addPtToRoute(route, direct_route->points[x]);
        }

        pass = 0;
    }
}

Result processShipment(Package* shipment, Map* map) {

    Result result = { 0 };

    // Calculate the closest route
    Point destination = { shipment->row, toupper(shipment->column) - 'A' };
    Route blueRoute = getBlueRoute();
    Route greenRoute = getGreenRoute();
    Route yellowRoute = getYellowRoute();

    int blueClosestIdx = getClosestPoint(&blueRoute, destination);
    int greenClosestIdx = getClosestPoint(&greenRoute, destination);
    int yellowClosestIdx = getClosestPoint(&yellowRoute, destination);

    double blueDist = distance(&destination, &blueRoute.points[blueClosestIdx]);
    double greenDist = distance(&destination, &greenRoute.points[greenClosestIdx]);
    double yellowDist = distance(&destination, &yellowRoute.points[yellowClosestIdx]);

    struct Route* selectedRoute = NULL;
    int closestIdx = -1;

    Point origin = { 0, -1 };
    Point dest = { destination.col, destination.row };
    Route directRoute = shortestPath((const Map*)&map, origin, dest); 
    /*  Direct route is the route from 0,0 to the destination.
    */

     //Added the points from direct route to which route is most efficient; Haven't figured how to add the route message.
    if (blueDist <= greenDist && blueDist <= yellowDist) {
        result.route_color = BLUE;

        addPtToRouteWrapper(&directRoute, &blueRoute);

        selectedRoute = &blueRoute;
        closestIdx = blueClosestIdx;
        result.diversion = (blueDist <= 1.0) ? NO_DIVERSION : DIVERT;
    }
    else if (greenDist <= blueDist && greenDist <= yellowDist) {
        result.route_color = GREEN;

        addPtToRouteWrapper(&directRoute, &greenRoute);

        selectedRoute = &greenRoute;
        closestIdx = greenClosestIdx;
        result.diversion = (greenDist <= 1.0) ? NO_DIVERSION : DIVERT;
    }
    else {
        result.route_color = YELLOW;

        addPtToRouteWrapper(&directRoute, &yellowRoute);

        selectedRoute = &yellowRoute;
        closestIdx = yellowClosestIdx;
        result.diversion = (yellowDist <= 1.0) ? NO_DIVERSION : DIVERT;
    }

    Point startPoint;
    Point backPath = { -1, -1 }; // Initialize with invalid row and col values

    if (result.diversion == DIVERT) {
        if (result.route_color == BLUE) {
            startPoint = blueRoute.points[blueClosestIdx];
        }   
        else if (result.route_color == GREEN) {
            startPoint = greenRoute.points[greenClosestIdx];
        }
        else {
            startPoint = yellowRoute.points[yellowClosestIdx];
        }

        Route possibleMoves = getPossibleMoves(&map, startPoint, backPath);

        // Print the possible moves
        for (int i = 0; i < possibleMoves.numPoints; i++) {
            printf("Move %d: (%d, %c)\n", i + 1, possibleMoves.points[i].row, possibleMoves.points[i].col + 'A');
        }
    }
    addRoute(&map, &blueRoute);
    addRoute(&map, &greenRoute);
    addRoute(&map, &yellowRoute);

    printf("Ship on %s LINE, %s\n", 
        result.route_color == BLUE ? "BLUE" : 
        result.route_color == GREEN ? "GREEN" : "YELLOW", 
        result.diversion == DIVERT ? "divert" : "no diversion");

    return result;

}