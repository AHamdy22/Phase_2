#include "AddValueAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager* pAppManager) : Action(pAppManager)
{
	LHS = "";
	RHS = 0.0;
}
Point p;
void AddValueAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member

	pOut->PrintMessage("Please enter the left hand side of the operation");
	LHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	pOut->PrintMessage("Please enter the right hand side of the operation");
	RHS = pIn->GetValue(pOut);
	pOut->ClearStatusBar();

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddValueAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	ValueAssign* pAssign = new ValueAssign(Corner, LHS, RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


void AddValueAssign::SetPosition(Point p)
{
	Position = p;
}

string AddValueAssign::GetLHS() const
{
	return LHS;
}

double AddValueAssign::GetRHS() const
{
	return RHS;
}