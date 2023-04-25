#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "delivery.h"
#include <string.h>

// you only have to call this method if you are not using the simulator
void run()
{
    display();
    Package shipment = { 0 };
    int inputRes = readInput(&shipment);
    if (inputRes == 2)
    {
        printf("Thanks for shipping with Seneca!");
        return;
    }
    else if (inputRes == 0)
    {
        return;
    }
    if (validateInputs(&shipment) == 0) return;

    Map map = populateMap();

    processShipment(&shipment, &map);
}

void display() 
{
    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n\n");
}

int readInput(Package* const shipment) 
{
    fgets(shipment->input, sizeof(shipment->input), stdin);

    return assignInputs(shipment);
}

int assignInputs(Package * const shipment) 
{
    if (strcmp(shipment->input, "0 0 x\n") == 0) {
        return 2; // to end the program
    }

    if (sscanf(shipment->input, "%lf %lf %d %c",
        &shipment->weight, &shipment->size, &shipment->row, &shipment->column) != 4) 
    {
        printf("Invalid input\n");
        return 0;
    }
    return 1;
}

int validateInputs(Package const * const shipment) 
{
    // Check if weight is valid
    if (!readWeight(shipment->weight)) 
    {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
        return 0;
    }

    // Check if size is valid
    if (!readSize(shipment->size)) 
    {
        printf("Invalid size\n");
        return 0;
    }

    // Check if destination is valid
    if (!readDestination(shipment->row, toupper(shipment->column))) 
    {
        printf("Invalid destination\n");
        return 0;
    }

    if (toupper(shipment->column) > 'Y' || shipment->row > MAP_ROWS) 
    {
        printf("Invalid destination\n");
        return 0;
    }

    return 1;
}

int readWeight(double weight) 
{
    return (weight >= 1 && weight <= 1000);
}

int readSize(double size) 
{
    return (size == 0.25 || size == 0.5 || size == 1.0);
}

int readDestination(int row, char column) 
{
    return (row >= 0 && row < MAP_ROWS&& isalpha(column) &&
            toupper(column) >= 'A' && toupper(column) <= 'Y');
}

int charToInt(char c) 
{
    int returnC = 0;
    char chara;
    //convert upper to low
    if (c >= 'A' && c <= 'Z') 
    {
        chara = c + 32;
    }
    if (c >= 'a' && c <= 'z') 
    {
        returnC = c - 'a';
    }
    return returnC;
}

char intToChar(int in) 
{
    char chara = 'A' + in;
    return chara;
}

void addPtToRouteWrapper(const Route * const directRoute, const Route * const route) 
{
    int pass = 0;
    for (int x = 0; x < directRoute->numPoints; x++)
    {   //nested for loop to check if the point is already a part of the route to prevent duplicates
        for (int y = 0; y < route->numPoints; y++)
        {
            if (route->points[y].col == directRoute->points[x].col && 
                route->points[y].row == directRoute->points[x].col)
            {
                pass = 1;
            }
        }
        if (pass == 0)
        {
            addPtToRoute(route, directRoute->points[x]);
        }
        pass = 0;
    }
}

void selectRoute(const DetailedRoute * const blue, 
                 const DetailedRoute * const green,
                 const DetailedRoute * const yellow,
                 const Route * const directRoute,
                 Result * const result,
                 Route * selectedRoute,
                 int * closestIdx
)
{
    if (blue->dist <= green->dist && blue->dist <= yellow->dist)
    {
        result->routeColor = BLUE;
        addPtToRouteWrapper(directRoute, &blue->route);
        selectedRoute = &blue->route;
        closestIdx = blue->closestIdx;
        result->diversion = (blue->dist <= 1.0) ? NO_DIVERSION : DIVERT;
    }
    else if (green->dist <= blue->dist && green->dist <= yellow->dist)
    {
        result->routeColor = GREEN;
        addPtToRouteWrapper(directRoute, &green->route);
        selectedRoute = &green->route;
        closestIdx = green->closestIdx;
        result->diversion = (green->dist <= 1.0) ? NO_DIVERSION : DIVERT;
    }
    else
    {
        result->routeColor = YELLOW;
        addPtToRouteWrapper(directRoute, &yellow->route);
        selectedRoute = &yellow->route;
        closestIdx = yellow->closestIdx;
        result->diversion = (yellow->dist <= 1.0) ? NO_DIVERSION : DIVERT;
    }
}

Result processShipment(Package* shipment, Map* map) 
{
    Result result = { 0 };

    // Calculate the closest route
    Point destination = { shipment->row, toupper(shipment->column) - 'A' };

    DetailedRoute blue = 
    {
        .route = getBlueRoute(),
        .closestIdx = getClosestPoint(&blue.route, destination),
        .dist = distance(&destination,
                         &blue.route.points[blue.closestIdx])
    };

    DetailedRoute green = 
    {
        .route = getGreenRoute(),
        .closestIdx = getClosestPoint(&green.route, destination),
        .dist = distance(&destination,
                         &green.route.points[green.closestIdx])
    };

    DetailedRoute yellow =
    {
        .route = getGreenRoute(),
        .closestIdx = getClosestPoint(&yellow.route, destination),
        .dist = distance(&destination,
                         &yellow.route.points[yellow.closestIdx])
    };

    Route* selectedRoute = NULL;
    int closestIdx = -1;

    Point origin = { 0, -1 };
    Point dest = { destination.col, destination.row };
    Route directRoute = shortestPath((const Map*)&map, origin, dest); 
    /*  Direct route is the route from 0,0 to the destination.
    */

     //Added the points from direct route to which route is most efficient; Haven't figured how to add the route message.
    selectRoute(&blue, &green, &yellow,
                &directRoute, &result, selectedRoute, &closestIdx);

    Point startPoint;
    Point backPath = { -1, -1 }; // Initialize with invalid row and col values

    if (result.diversion == DIVERT) 
    {
        if (result.routeColor == BLUE)
        {
            startPoint = blue.route.points[blue.closestIdx];
        }   
        else if (result.routeColor == GREEN)
        {
            startPoint = green.route.points[green.closestIdx];
        }
        else 
        {
            startPoint = yellow.route.points[yellow.closestIdx];
        }

        Route possibleMoves = getPossibleMoves(&map, startPoint, backPath);

        // Print the possible moves
        for (int i = 0; i < possibleMoves.numPoints; i++) 
        {
            printf("Move %d: (%d, %c)\n", i + 1, possibleMoves.points[i].row, possibleMoves.points[i].col + 'A');
        }
    }

    addRoute(&map, &blue.route);
    addRoute(&map, &green.route);
    addRoute(&map, &yellow.route);

    printf("Ship on %s LINE, %s\n", 
        result.routeColor == BLUE ? "BLUE" :
        result.routeColor == GREEN ? "GREEN" : "YELLOW",
        result.diversion == DIVERT ? "divert" : "no diversion");

    return result;
}
