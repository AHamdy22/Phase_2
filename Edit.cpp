#include "Edit.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Edit::Edit(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Edit::ReadActionParameters()
{
}



void Edit::Execute()
{

    Statement* clickedStat = pManager->GetSelectedStatement();

    if (clickedStat)
    {

        clickedStat->EditStatement(pManager, clickedStat->GetPosition());

        pManager->UpdateInterface();

    }
    else
    {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Edit Action: There is no selected statement to edit");
    }
}