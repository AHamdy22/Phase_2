#include "AddStart.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
using namespace std;

AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void AddStart::ReadActionParameters()
{

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

}

void AddStart::Execute()
{
	ReadActionParameters();

	Point Corner;
	Corner.x = Position.x - UI.START_WDTH / 2;
	Corner.y = Position.y;

	Start* pStart = new Start(Corner);

	pManager->AddStatement(pStart);

}

void AddStart::SetPosition(Point p)
{
	Position = p;
}