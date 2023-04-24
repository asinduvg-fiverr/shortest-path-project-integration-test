#ifndef DELIVERY_H
#define DELIVERY_H

#define MAX_WEIGHT 1000
#define MAX_SIZE 36

struct Package {
    double weight;
    double size;
    int row;
    char column;
    char input[20];
};

struct Truck {
    double max_weight;
    double max_size;
    int row;
    char column;
};

struct Move {
    int row;
    char col;
};

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
int readInput(struct Package* shipment);
int assignInputs(struct Package* shipment);
int validateInputs(struct Package* shipment);
int readWeight(double weight);
int readSize(double size);
int readDestination(int row, char column);
Result processShipment(struct Package* shipment, struct Map* map);
int charToInt(char character);  //Returns the character converted to int: E.g A/a = 0, B/b = 1,.... etc
char intToChar(int in);    //does the thing above in reverse: e.g 0 = A, 1 = B.... etc

#endif