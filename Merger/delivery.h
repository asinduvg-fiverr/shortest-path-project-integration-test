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
    double weight;  //current weight
    double size;    //current size
};

struct Move {
    int row;
    char col;
};

struct Storage {
    struct Package storage[20];
    int numPackage;
};

struct PackageNode {
    struct Package package;
    struct PackageNode* next;
};


void display();
int readInput(struct Package* shipment);
int readWeight(double weight);
int readSize(double size);
int readDestination(int row, char column);
void processShipment(struct Package* shipment, struct Map map, struct Route* selectedRoute, const char* routeColor);
void addPackageToTruck(struct Package* shipment, struct Truck* truckG, struct Truck* truckB, struct Truck* truckY, struct Map map, struct Storage* storage);
void addToStorage(struct Package* shipment, struct Storage* storage);

#endif
