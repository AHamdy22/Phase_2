#pragma once
#ifndef ADD_CONNECTORS_h
#define ADD_CONNECTORS_h

#include "Actions\Action.h"
#include "Connector.h"
class AddConnectors : public Action
{
private:
	Point StartPoint;	//the start point of the connector
	Point EndPoint;		//the end point of the connector
	Connector* pConn; //the connector to be added
public:
	AddConnectors(ApplicationManager* pappmanager);

	//read read statements position
	void ReadActionParameters();

	//create and add a read statement to the list of statements
	void Execute();

};
#endif