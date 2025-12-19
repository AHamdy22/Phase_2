#include "AddDeclare.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"


AddDeclare::AddDeclare(ApplicationManager* pAppManager) : Action(pAppManager)
{}
void AddDeclare::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Declare Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();


	pOut->PrintMessage("Please enter the data type for the variable declaration");
	pOut->ClearStatusBar();
	DataType = pIn->GetDataType(pOut);



	pOut->PrintMessage("Please enter the variable name");
	Var = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}

void AddDeclare::SetPosition(Point p)
{
	Position = p;
}

string AddDeclare::GetVar() const
{
	return Var;
}



void AddDeclare::Execute()
{
	ReadActionParameters();



	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Declare* pAssign = new Declare(Corner, DataType, Var);

	pManager->AddStatement(pAssign);
}


