#ifndef ADD_OPERATOR_ASSIGN_H
#define ADD_OPERATOR_ASSIGN_H

#include "Actions\Action.h"
#include "Statements\..\OperatorAssign.h"

class AddOperatorAssign : public Action
{
private:


	Point Position;
	string LHS;
	string varOP1;
	double valOP1;
	string varOP2;
	double valOP2;
	char Operation;


public:
	AddOperatorAssign(ApplicationManager* pAppManager);


	virtual void ReadActionParameters();


	virtual void Execute();

};

#endif


