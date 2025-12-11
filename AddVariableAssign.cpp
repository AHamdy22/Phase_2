#include "AddVariableAssign.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVariableAssign::AddVariableAssign(ApplicationManager* pAppManager) : Action(pAppManager)
{
	LHS = "";
	RHS = "";
	Position.x = -1;
}
Point p2;
void AddVariableAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x == -1)
	{
		//Read the (Position) parameter
		pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();

	}

	//TODO: Ask the user in the status bar to enter the LHS and set the data member

	pOut->PrintMessage("Please enter the left hand side of the operation");
	pIn->GetPointClicked(p2);
	pOut->ClearStatusBar();
	LHS = pIn->GetVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	pOut->PrintMessage("Please enter the right hand side of the operation");
	pIn->GetPointClicked(p2);
	pOut->ClearStatusBar();
	RHS = pIn->GetVariable(pOut);

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddVariableAssign::SetPosition(Point p)
{
	Position = p;
}

string AddVariableAssign::GetLHS() const
{
	return LHS;
}

string AddVariableAssign::GetRHS() const
{
	return RHS;
}



void AddVariableAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	VariableAssign* pAssign = new VariableAssign(Corner, LHS, RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

