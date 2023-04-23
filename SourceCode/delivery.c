#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "delivery.h"
#include "math.h"
#include<stdbool.h>



double calEdistance(int x1, char y1, int x2, char y2) {
    let num1 = (int)(y1-'A');
    let num2 = (int)(y2 - 'A');

    distanceY = int(y1) - int(y2);
    let distance = Math.sqrt(Math.pow(x2-x1, 2) + Math.pow(num2-num1, 2));
    return distance;
};

// Compare three trucks based on available weight and volume and distance.  Can use spaceInTruck() and calEdistancce() to determine
struct Truck* compTrucks(struct Truck* t1, struct Truck* t2, struct Truck* t3) {
    double t1_capacity = t1->weight* t1->volume;
    double t2_capacity = t2->weight * t2->volume;
    double t3_capacity = t3->weight * t3->volume;
    if (t1_capacity > t2_capacity && t1_capacity > t2_capacity) {
        return t1
    };
    if (t2_capacity > t1_capacity && t2_capacity > t3_capacity) {
        return t2
    };
    if (t3_capacity > t1_capacity && t3_capacity > t2_capacity) {
        return t3
    };

};

// Update truck capacity with package weight and volume.
void updateTcap(struct Truck* truck, struct Package* pkg) {
    truck->weight -= pkg->weight;
    truck->volume -= pkg->size;

};

// Read package information: weight, size, row, and column.
bool readPack(struct Package* pkg, char* input) {

    int numFields = sscanf(input, "%lf %lf %d %c", &pkg->weight, &pkg->size, &pkg->row, &pkg->column);
    if (numFields != 4) {
        return false;
    }
    // convert column to lowercase if it's uppercase
    if (pkg->column >= 'A' && pkg->column <= 'Z') {
        pkg->column += 'a' - 'A';
    }
    return true;
};

//Add package to storage
void addToStorage(struct Package* pack, struct Package* store[]) {
    // find the first empty slot in the storage array and add the package
    for (int i = 0; i < 20; i++) {
        if (store[i] == NULL) {
            store[i] = pack;
            return;
        }
    }
};

//Remove package from storage and returns a referance of that package so it can be added to a truck
struct Package* removeFromStorage(struct Package* store[]) {
    for (int i = 0; i < 20; i++) {
        if (store[i] != NULL) {
            struct Package* pkg = store[i];
            store[i] = NULL;
            return pkg;
        }
    }
    return NULL;


};
//test

//check space in truck for package    Returns true if there is space in the truck| False if there isn't space in truck
//Should check for volume and weight


bool spaceInTruck(struct Truck* truck, struct Package* pack) {
    if ((truck->weight + pack->weight) <= 2000 && (truck->volume + pack->size) <= 100) {
        return true;
    }
    return false;
}