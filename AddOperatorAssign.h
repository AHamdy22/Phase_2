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


	void SetPosition(Point p);

	string GetLHS() const;

	string GetvarOP1() const;

	double GetvalOP1() const;

	string GetvarOP2() const;

	double GetvalOP2() const;

	char GetOperation() const;

	virtual void Execute();

};

#endif


