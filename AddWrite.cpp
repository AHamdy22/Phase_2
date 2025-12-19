#include "AddWrite.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	pOut->PrintMessage("Enter the variable name: ");
	VarName = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}

void AddWrite::Execute()
{
	ReadActionParameters();
	//Calculating left corner of read statement block
	Point Corner;
	Corner.x = Position.x - UI.READ_WDTH / 2;
	Corner.y = Position.y;

	Write* pWrite = new Write(Corner, VarName);

	pManager->AddStatement(pWrite); // Adds the created statement to application manger's statement list
}

void AddWrite::SetPosition(Point p)
{
	Position = p;
}

string AddWrite::GetVarName() const
{
	return VarName;
}