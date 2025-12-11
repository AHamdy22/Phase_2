#include "Cut.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Cut::Cut(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Cut::ReadActionParameters()
{
}



void Cut::Execute()
{
    Output* pOut = pManager->GetOutput();


    Statement* clickedStat = pManager->GetSelectedStatement();

    if (clickedStat)
    {

        pManager->SetClipboard(clickedStat);

        clickedStat->SetCut(true);

        clickedStat->GetStatementCut(pManager);

        pOut->PrintMessage("Cut Action: Selected statement has been cut");

    }
    else
        pOut->PrintMessage("Cut Action: There is no selected statement to cut");
}