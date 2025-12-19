#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"

Copy::Copy(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Copy::ReadActionParameters()
{}

void Copy::Execute()
{
    Output* pOut = pManager->GetOutput();


    Statement* clickedStat = pManager->GetSelectedStatement();

    if (clickedStat)
    {

        pManager->SetClipboard(clickedStat);

        clickedStat->SetCopied(true);

        pOut->PrintMessage("Copy Action: Selected statement has been copied");

    }
    else
        pOut->PrintMessage("Copy Action: There is no selected statement to copy");
}