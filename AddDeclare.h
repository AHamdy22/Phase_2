#ifndef ADD_Declare_H
#define ADD_Declare_H

#include "Actions\Action.h"
#include "Statements\..\Declare.h"


class AddDeclare : public Action
{
private:
	

	Point Position;
	string DataType;
	string Var;

	

public:
	AddDeclare(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};

#endif
