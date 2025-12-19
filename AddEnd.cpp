#include "AddEnd.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"


AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddEnd::ReadActionParameters()
{

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

}

void AddEnd::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.START_WDTH / 2;
	Corner.y = Position.y;

	End* pEnd = new End(Corner);

	pManager->AddStatement(pEnd);
}

void AddEnd::SetPosition(Point p)
{
	Position = p;
}