#pragma once
#include "Actions\Action.h"
#include "Connector.h"

class AddConnector : public Action
{
private:
	Point StartPoint; // Position where the user clicks to start the connector
	Point EndPoint;   // Position where the user clicks to end the connector

public:
	AddConnector(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();
};