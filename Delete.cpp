#include "Delete.h"

#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;


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
    if (clickedStat)
    {
        pOut->PrintMessage("Delete Action: Selected Statement has been deleted");
        pManager->DeleteStatement(clickedStat);
        pManager->SetSelectedStatement(NULL);
    }
    else
        pOut->PrintMessage("Delete Action: There is no selected statement to delete");
}