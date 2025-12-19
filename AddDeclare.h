#ifndef ADD_Declare_H
#define ADD_Declare_H

#include "Actions\Action.h"
#include "Statements\..\Declare.h"


class AddDeclare : public Action
{
private:


	Point Position;
	string Var;
	string DataType;


public:
	AddDeclare(ApplicationManager* pAppManager);


	virtual void ReadActionParameters();


	void SetPosition(Point p);


	string GetVar() const;

	virtual void Execute();

};

#endif