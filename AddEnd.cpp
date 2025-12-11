#include "AddEnd.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager)
{
	Position.x = -1;
}

void AddEnd::ReadActionParameters()
{

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if(Position.x == -1)
	{
		pOut->PrintMessage("End Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("END STATEMENTS CAN NOT BE EDITED !");
	}

}

void AddEnd::SetPosition(Point p)
{
	Position = p;
}

void AddEnd::Execute()
{
	ReadActionParameters();

	
	Point Corner;
	Corner.x = Position.x - UI.START_WDTH / 2;
	Corner.y = Position.y;

	End* pAssign = new End(Corner);
	
	pManager->AddStatement(pAssign);

}