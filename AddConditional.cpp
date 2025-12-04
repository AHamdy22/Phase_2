#include "AddConditional.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConditional::AddConditional(ApplicationManager* pAppManager) : Action(pAppManager)
{
	LHS = "";
	ValueRHS = 0;
	VariableRHS = "";
	CompOperator = "";
}

Point P;
void AddConditional::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member

	pOut->PrintMessage("Please enter the left hand side of the operation");
	string stored;
	pIn->GetPointClicked(P);
	pOut->ClearStatusBar();
	while (1) {
		stored = pIn->GetVariable(pOut);
		if (IsVariable(stored))
		{
			LHS = stored;
			break;
		}
		else
			pOut->PrintMessage("Please enter valid Variable");
	}

	//TODO: Ask the user in the status bar to enter the CompOperator and set the data member

	pOut->PrintMessage("Please enter the CompOperator of the operation");
	pIn->GetPointClicked(P);
	pOut->ClearStatusBar();
	CompOperator = pIn->GetCompOperator(pOut);
	

	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	pOut->PrintMessage("Please enter the right hand side of the operation");
	pIn->GetPointClicked(P);
	pOut->ClearStatusBar();
	while (1) {
		stored = pIn->GetString(pOut);
		if (IsValue(stored))
		{
			ValueRHS = stod(stored);
			break;
		}
		else if (IsVariable(stored))
		{
			VariableRHS = stored;
			break;
		}
		else
			pOut->PrintMessage("Please enter valid value or Variable");
	}
	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddConditional::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Top;
	Top.x = Position.x;
	Top.y = Position.y;

	Conditional* pAssign = new Conditional(Top, LHS, ValueRHS, VariableRHS, CompOperator);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}