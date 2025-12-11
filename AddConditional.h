#ifndef ADD_CONDITIONAL_ASSIGN_H
#define ADD_CONDITIONAL_ASSIGN_H

#include "Actions\Action.h"
#include "Statements\..\Conditional.h"


class AddConditional : public Action
{
private:
	

	Point Position;
	string LHS;	
	double ValueRHS;
	string VariableRHS;
	string CompOperator;



public:
	AddConditional(ApplicationManager* pAppManager);

	
	void ReadActionParameters();


	void SetPosition(Point p);

	string GetLHS() const;

	double GetValueRHS() const;

	string GetVariableRHS() const;

	string GetCompOperator() const;

	void Execute();

};

#endif

