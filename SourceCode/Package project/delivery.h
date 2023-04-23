#ifndef Delivery_h
#define Delivery_h

// Truck structure with attributes: weight, volume, row, and column.
struct Truck {
    double weight;
    double volume;
    int row;
    char column;
};

// Package structure with attributes: weight, size, row, and column.
struct Package {
    double weight;
    double size;
    int row;
    char column;
};

struct Company {    //This structure might be useful since we can just use it to access the things we need.
    struct Truck trucks[3]; //represents the trucks we have
    struct Package storage[20]; //represents the packages we have in storage
};

//struct Storage {    //Struct is used to store packages that haven't been sent
//    Package storedPackages [20];    //Array of packages to store stored pacakges, don't know if pointing would work in C
//};

// Function prototypes

// Calculate Euclidean distance between two points. //needs parameters
/*Explination to implementer: the equation is   sqrt(x^2 + y^2) x and y are the distance between the two points.
*/
double calEdistance();

// Compare three trucks based on available weight and volume and distance.  Can use spaceInTruck() and calEdistancce() to determine
struct Truck* compTrucks(struct Truck* t1, struct Truck* t2, struct Truck* t3);

// Update truck capacity with package weight and volume.
void updateTcap(struct Truck* truck, struct Package* pkg);

// Read package information: weight, size, row, and column.
bool readPack(struct Package* pkg, char* input);

//Add package to storage
void addToStorage(struct Package* pack, struct Package* store[]);

//Remove package from storage and returns a referance of that package so it can be added to a truck
struct Package* removeFromStorage(struct Package* store[]);
//test

//check space in truck for package    Returns true if there is space in the truck| False if there isn't space in truck
//Should check for volume and weight
bool spaceInTruck(struct Truck* truck, struct Package* pack);




#endif
