#include "simulator.h"

Simulator simulator = { 0 };

void send(const char* inputStr)
{
	simulator.result = (Result) { 0 };
	Package shipment = { 0 };
	strcpy(shipment.input, inputStr);
	Map map = populateMap();

	int input = assignInputs(&shipment);

	if (input == 0 || input == 2)
	{
		return; // program returns empty result on invalid input or exit
	}

	if (validateInputs(&shipment) == 0)
	{
		return;
	}

	simulator.result = processShipment(&shipment, &map);
}

Result receive()
{
	return simulator.result;
}
