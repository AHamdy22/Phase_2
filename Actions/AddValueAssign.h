#ifndef ADD_VALUE_ASSIGN_H
#define ADD_VALUE_ASSIGN_H

#include "Action.h"
#include "..\Statements\ValueAssign.h"

class AddValueAssign : public Action
{
private:
	

	Point Position;
	string LHS;
	double RHS;

	

public:
	AddValueAssign(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	void SetPosition(Point p);

	string GetLHS() const;

	double GetRHS() const;

};

#endif