#include "AddRead.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
using namespace std;

AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager)
{
	Position.x = -1;
}

void AddRead::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x==-1)
	{
		//Read the (Position) parameter
		pOut->PrintMessage("Read Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}

	pOut->PrintMessage("Enter the variable name: ");
	VarName = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}

void AddRead::SetPosition(Point p)
{
	Position = p;
}

string AddRead::GetVarName() const
{
	return VarName;
}

void AddRead::Execute()
{
	ReadActionParameters();
	//Calculating left corner of read statement block
	Point Corner;
	Corner.x = Position.x - UI.READ_WDTH / 2;
	Corner.y = Position.y;

	Read* pRead = new Read(Corner, VarName);

	pManager->AddStatement(pRead); // Adds the created statement to application manger's statement list
}