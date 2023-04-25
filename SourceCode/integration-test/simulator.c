#include "simulator.h"

Simulator simulator = { 0 };

void send(const char* inputStr)
{
	simulator.result = (Result) { 0 };
	Package shipment = { 0 };
	strcpy(shipment.input, inputStr);
	Map map = { 0 };

	if (assignInputs(&shipment) == 0)
	{
		return;
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
