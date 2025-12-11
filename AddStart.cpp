#include "AddStart.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;


AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{
	Position.x = -1;
}

void AddStart::ReadActionParameters()
{
	
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x == -1)
	{
		pOut->PrintMessage("Start Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	else
	{

		pOut->PrintMessage("START STATEMENTS CAN NOT BE EDITED !");

	}

}

void AddStart::SetPosition(Point p)
{
	Position = p;
}

void AddStart::Execute()
{
	ReadActionParameters();

	
	Point Corner;
	Corner.x = Position.x - UI.START_WDTH / 2;
	Corner.y = Position.y;

	Start* pAssign = new Start(Corner);


	pManager->AddStatement(pAssign);

}