#ifndef ADD_CONDITIONAL_H
#define ADD_CONDITIONAL_H

#include "Actions\Action.h"
#include "Statements\..\Conditional.h"

class AddConditional : public Action
{
private:

	Point Position;
	string LHS;	//Left Handside of the assignment (name of a variable)
	double ValueRHS;	//Right Handside (Value)
	string VariableRHS;	//Right Handside (variable)
	string CompOperator;

	//Position where the user clicks to add the stat.
	//TODO: you should add LHS and RHS of the assignment statement as parameters

public:
	AddConditional(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();

	void SetPosition(Point p);

	string GetLHS() const;

	double GetValueRHS() const;

	string GetVariableRHS() const;

	string GetCompOperator() const;


};

#endif