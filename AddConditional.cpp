#include "AddConditional.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;


AddConditional::AddConditional(ApplicationManager* pAppManager) : Action(pAppManager)
{
	LHS = "";
	ValueRHS = 0;
	VariableRHS = "";
	CompOperator = "";
	Position.x = -1;
}

Point P;
void AddConditional::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x == -1)
	{
		pOut->PrintMessage("Conditional Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}


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

	pOut->PrintMessage("Please enter the CompOperator of the operation");
	pIn->GetPointClicked(P);
	pOut->ClearStatusBar();
	CompOperator = pIn->GetCompOperator(pOut);


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
	
}

void AddConditional::SetPosition(Point p)
{
	Position = p;
}

string AddConditional::GetLHS() const
{
	return LHS;
}

double AddConditional::GetValueRHS() const
{
	return ValueRHS;
}

string AddConditional::GetVariableRHS() const
{
	return VariableRHS;
}

string AddConditional::GetCompOperator() const
{
	return CompOperator;
}



void AddConditional::Execute()
{
	ReadActionParameters();


	
	Point Top;
	Top.x = Position.x;
	Top.y = Position.y;

	Conditional* pAssign = new Conditional(Top, LHS, ValueRHS, VariableRHS, CompOperator);
	

	pManager->AddStatement(pAssign);
}