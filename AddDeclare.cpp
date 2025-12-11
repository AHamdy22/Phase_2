#include "AddDeclare.h"




#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;


AddDeclare::AddDeclare(ApplicationManager* pAppManager) : Action(pAppManager)
{
	DataType = "";
	Var = "";
	Position.x = -1;
}
Point p1;
void AddDeclare::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x == -1)
	{
		pOut->PrintMessage("Declare Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}


	

	pOut->PrintMessage("Please enter the data type for the variable declaration");
	pIn->GetPointClicked(p1);
	pOut->ClearStatusBar();
	DataType = pIn->GetDataType(pOut);

	

	pOut->PrintMessage("Please enter the variable name");
	pIn->GetPointClicked(p1);
	pOut->ClearStatusBar();
	Var = pIn->GetVariable(pOut);

	
}

void AddDeclare::SetPosition(Point p)
{
	Position = p;
}

string AddDeclare::GetDataType() const
{
	return DataType;
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



