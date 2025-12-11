#include "Select.h"


#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Select::Select(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Select::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    //Read the (Position) parameter
    pOut->PrintMessage("Select Action: Click on a statement to select");

    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

}

void Select::Execute()
{
    ReadActionParameters();

    Statement* clickedStat = pManager->GetStatement(Position);

    if (clickedStat)
    {
        Statement* prevSelected = pManager->GetSelectedStatement();
        if (prevSelected == clickedStat)
        {
            clickedStat->SetSelected(false);
            pManager->SetSelectedStatement(nullptr);
        }
        else
        {
            if (prevSelected)
                prevSelected->SetSelected(false);

            clickedStat->SetSelected(true);
            pManager->SetSelectedStatement(clickedStat);
        }
        pManager->UpdateInterface();
    }
}