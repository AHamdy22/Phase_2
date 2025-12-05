#include "Delete.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
    //Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    //Read the (Position) parameter
    pOut->PrintMessage("Select Statement: Click to add the statement");

    //pIn->GetPointClicked(Position);
    //pOut->ClearStatusBar();

}

void Delete::Execute()
{
    ReadActionParameters();

    Statement* clickedStat = pManager->GetSelectedStatement();
    if (clickedStat)
    {
		pManager->DeleteStatement(clickedStat);
		pManager->SetSelectedStatement(NULL);
    }
}