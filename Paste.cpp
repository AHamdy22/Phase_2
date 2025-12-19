#include "Paste.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"

//constructor: set the ApplicationManager pointer inside this action
Paste::Paste(ApplicationManager* pAppManager) : Action(pAppManager)
{
    InClipboard = pManager->GetClipboard();
}

void Paste::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    if (InClipboard)
    {
        pOut->PrintMessage("Paste Action: Click to paste");
        pIn->GetPointClicked(Position);
        pOut->ClearStatusBar();

    }
    else
        pOut->PrintMessage("There is no statement to paste");
}

void Paste::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    if (InClipboard)
    {
        InClipboard->PasteStatement(InClipboard, Position, pOut, pManager);
    }
}