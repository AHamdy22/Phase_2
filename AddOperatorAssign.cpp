#include "AddOperatorAssign.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager* pAppManager) : Action(pAppManager)
{
	LHS = "";
	varOP1 = "";
	valOP1 = 0.0;
	varOP2 = "";
	valOP2 = 0.0;
	Position.x = -1;
}
Point p3;
void AddOperatorAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	string Firstop;
	string Secondop;

	if (Position.x == -1)
	{
		//Read the (Position) parameter
		pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}

	//TODO: Ask the user in the status bar to enter the LHS and set the data member

	pOut->PrintMessage("Please enter the left hand side of the operation");
	pIn->GetPointClicked(p3);
	pOut->ClearStatusBar();
	LHS = pIn->GetVariable(pOut);



	pOut->PrintMessage("Please enter the first operant of the operation");
	pIn->GetPointClicked(p3);
	pOut->ClearStatusBar();


	while (1)
	{
		Firstop = pIn->GetString(pOut);

		if (IsValue(Firstop))
		{
			valOP1 = stod(Firstop);
			break;
		}
		else if (IsVariable(Firstop))
		{
			varOP1 = Firstop;
			break;
		}
		else
			pOut->PrintMessage("Please enter a valid operant");
	}

	pOut->PrintMessage("Please enter the arthmetic operant of the operation");
	pIn->GetPointClicked(p3);
	pOut->ClearStatusBar();

	Operation = pIn->GetArithOperator(pOut);
	pOut->PrintMessage("Please enter the second operant of the operation");
	pIn->GetPointClicked(p3);
	pOut->ClearStatusBar();


	while (1)
	{
		Secondop = pIn->GetString(pOut);

		if (IsValue(Secondop))
		{
			valOP2 = stod(Secondop);
			break;

		}
		else if (IsVariable(Secondop))
		{
			varOP2 = Secondop;
			break;
		}
		else
			pOut->PrintMessage("Please enter a valid operant");
	}
}

void AddOperatorAssign::SetPosition(Point p)
{
	Position = p;
}

string AddOperatorAssign::GetLHS() const
{
	return LHS;
}

string AddOperatorAssign::GetvarOP1() const
{
	return varOP1;
}

double AddOperatorAssign::GetvalOP1() const
{
	return valOP1;
}

string AddOperatorAssign::GetvarOP2() const
{
	return varOP2;
}

double AddOperatorAssign::GetvalOP2() const
{
	return valOP2;
}

char AddOperatorAssign::GetOperation() const
{
	return Operation;
}


void AddOperatorAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	OperatorAssign* pAssign = new OperatorAssign(Corner, LHS, valOP1, varOP1, valOP2, varOP2, Operation);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}
