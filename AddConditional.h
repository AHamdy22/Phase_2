#ifndef ADD_CONDITIONAL_ASSIGN_H
#define ADD_CONDITIONAL_ASSIGN_H

#include "Actions\Action.h"
#include "Statements\..\Conditional.h"

//Add Value Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user (one of the parameters of this action)
// 2 - Getting the LHS and RHS of the statement from the user (some of the parameters of this action)
// 3 - Creating an object of Assignment class and passing it parameters
// 4 - Adding the created object to the list of statements of the application manager
class AddConditional : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

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

};

#endif

