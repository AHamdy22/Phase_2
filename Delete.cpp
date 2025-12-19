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
}

void Delete::Execute()
{
   
    Output* pOut = pManager->GetOutput();
    Statement* clickedStat = pManager->GetSelectedStatement();
    Connector* clickedConn = pManager->GetSelectedConnector();

    if (clickedStat)
    {
        pManager->DeleteStatement(clickedStat);
        pManager->SetSelectedStatement(NULL);
		pOut->PrintMessage("Statement deleted");
    }
    if (clickedConn)
    {
        pManager->DeleteConnector(clickedConn);
        pManager->SetSelectedConnector(NULL);
		pOut->PrintMessage("Connector deleted");
    }
    pManager->UpdateInterface();
}