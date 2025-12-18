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
    pOut->PrintMessage("Select Statement: Click to add the statement");

    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

}

void Select::Execute()
{
    ReadActionParameters();

	Statement* clickedStat = pManager->GetStatement(Position);
    Connector* clickedConn = pManager->GetConnector(Position);

    if (clickedStat)
    {
        Connector* prevConn = pManager->GetSelectedConnector();
        if (prevConn)
        {
            prevConn->SetSelected(false);
            pManager->SetSelectedConnector(NULL);
        }

        Statement* prevStat = pManager->GetSelectedStatement();

        if (prevStat == clickedStat)
        {
            clickedStat->SetSelected(false);
            pManager->SetSelectedStatement(NULL);
        }
        else
        {
            if (prevStat)
                prevStat->SetSelected(false);

            clickedStat->SetSelected(true);
            pManager->SetSelectedStatement(clickedStat);
        }

        pManager->UpdateInterface();
    }
    else if (clickedConn)
    {
        Statement* prevStat = pManager->GetSelectedStatement();
        if (prevStat)
        {
            prevStat->SetSelected(false);
            pManager->SetSelectedStatement(NULL);
        }

        Connector* prevConn = pManager->GetSelectedConnector();

        if (prevConn == clickedConn)
        {
            clickedConn->SetSelected(false);
            pManager->SetSelectedConnector(NULL);
        }
        else
        {
            if (prevConn)
                prevConn->SetSelected(false);

            clickedConn->SetSelected(true);
            pManager->SetSelectedConnector(clickedConn);
        }

        pManager->UpdateInterface();
    }
}