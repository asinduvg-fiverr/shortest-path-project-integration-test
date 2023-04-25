#ifndef DELIVERY_H
#define DELIVERY_H

#define MAX_WEIGHT 1000
#define MAX_SIZE 36

#include "mapping.h"

typedef struct
{
    double weight;
    double size;
    int row;
    char column;
    char input[20];
} Package;

typedef struct
{
    double maxWeight;
    double maxSize;
    int row;
    char column;
} Truck;

typedef struct
{
    int row;
    char col;
} Move;

typedef enum
{
    DIVERT,
    NO_DIVERSION
} Diversion;

typedef struct
{
    int routeColor;
    Diversion diversion;
} Result;


void display();
int readInput(Package* shipment);
int assignInputs(Package* shipment);
int validateInputs(Package* shipment);
int readWeight(double weight);
int readSize(double size);
int readDestination(int row, char column);
Result processShipment(Package* shipment, Map* map);
int charToInt(char character);  //Returns the character converted to int: E.g A/a = 0, B/b = 1,.... etc
char intToChar(int in);    //does the thing above in reverse: e.g 0 = A, 1 = B.... etc

void addPtToRouteWrapper(const Route* const direct_route, const Route* const route);
void selectRoute(const DetailedRoute* const blue,
    const DetailedRoute* const green,
    const DetailedRoute* const yellow,
    const Route* const direct_route,
    Result* const result,
    Route* selected_route,
    int* closest_idx
);

#endif
