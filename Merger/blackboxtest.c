#include <stdio.h>
#include "delivery.h"
#include "mapping.h"

void test_readWeight() {
    printf("Testing readWeight...\n");
    printf("Test 1: (500) ");
    if (readWeight(500)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 2: (0) ");
    if (!readWeight(0)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 3: (1001) ");
    if (!readWeight(1001)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }
    printf("\n");
}

void test_readSize() {
    printf("Testing readSize...\n");
    printf("Test 1: (0.25) ");
    if (readSize(0.25)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 2: (0.75) ");
    if (!readSize(0.75)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 3: (1.0) ");
    if (readSize(1.0)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }
    printf("\n");
}

void test_readDestination() {
    printf("Testing readDestination...\n");
    printf("Test 1: (5, 'C') ");
    if (readDestination(5, 'C')) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 2: (25, 'C') ");
    if (!readDestination(25, 'C')) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }

    printf("Test 3: (5, 'Z') ");
    if (!readDestination(5, 'Z')) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }
    printf("\n");
}

void test_getClosestPoint() {
    printf("Testing getClosestPoint...\n");
    struct Route testRoute;
    testRoute.numPoints = 3;
    testRoute.points[0] = (struct Point){ 0, 0 };
    testRoute.points[1] = (struct Point){ 5, 5 };
    testRoute.points[2] = (struct Point){ 2, 2 };

    struct Point testPoint = { 3, 3 };

    int closestIdx = getClosestPoint(&testRoute, testPoint);

    printf("Test 1: Closest Point Index ");
    if (closestIdx == 2) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }
    printf("\n");
}

void test_distance() {
    printf("Testing distance...\n");
    struct Point p1 = { 3, 3 };
    struct Point p2 = { 6, 6 };

    double dist = distance(&p1, &p2);

    printf("Test 1: Distance ");
    if (dist - 4.24264 < 0.00001) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
    }
    printf("\n");
}

int main() {
    test_readWeight();
    test_readSize();
    test_readDestination();
    test_getClosestPoint();
    test_distance();

    return 0;
}
