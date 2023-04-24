#ifndef DELIVERY_H
#define DELIVERY_H

#define MAX_WEIGHT 1000
#define MAX_SIZE 36

#include "mapping.h"

typedef struct {
    double weight;
    double size;
    int row;
    char column;
    char input[20];
} Package;

typedef struct {
    double max_weight;
    double max_size;
    int row;
    char column;
} Truck;

typedef struct {
    int row;
    char col;
} Move;

typedef enum {
    DIVERT,
    NO_DIVERSION
} Diversion;


typedef struct {
    char route_color[6];
    Diversion diversion;
    const char* divert_message;
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

#endif