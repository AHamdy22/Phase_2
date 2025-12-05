#ifndef ADD_DECLARE_VARIABLE_H
#define ADD_DECLARE_VARIABLE_H

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


	void SetPosition(Point p);

	string GetDataType() const;

	string GetVar() const;

	virtual void Execute();

};

#endif

