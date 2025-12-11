#ifndef ADD_END_H
#define ADD_END_H

#include "Actions\Action.h"
#include "Statements\..\End.h"


class AddEnd : public Action
{
private:
	

	Point Position;

public:
	AddEnd(ApplicationManager* pAppManager);


	void ReadActionParameters();

	void SetPosition(Point p);

	void Execute();

};

#endif