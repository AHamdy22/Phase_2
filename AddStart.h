#ifndef ADD_START_H
#define ADD_START_H

#include "Actions\Action.h"
#include "Statements\..\Start.h"


class AddStart : public Action
{
private:
	
	Point Position;	
public:
	AddStart(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void SetPosition(Point p);

	void Execute();

};

#endif