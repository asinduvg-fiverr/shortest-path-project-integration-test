#ifndef DELIVERY_H
#define DELIVERY_H

// Structure to represent a truck
struct Truck {
    double weight;
    double volume;
    char* route;
};

// Structure to represent a package
struct Package {
    double weight;
    double size;
    int row;
    char column;
};

// Function prototypes
double euclidean_distance(int x1, int y1, int x2, int y2);
int shortest_path(int startX, int startY, int endX, int endY, char** map);
struct Truck* compare_trucks(struct Truck* truck1, struct Truck* truck2);
void update_truck_capacity(struct Truck* truck, struct Package* package);
int read_package_information(struct Package* package);
int validate_package_input(struct Package* package);

#endif // DELIVERY_H
