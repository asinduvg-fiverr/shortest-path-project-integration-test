#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "delivery.h"


int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	struct Map routeMap1 = addRoute(&routeMap, &greenRoute);
	struct Map routeMap2 = addRoute(&routeMap1, &yellowRoute);

	printMap(&routeMap2, 1, 1);
	printf("---------------");
	printf("Seneca Deliveries");
	printf("---------------");
	printf("Enter shipment weight, box size and destination (0 0 x to stop): ");

	return 0;
}