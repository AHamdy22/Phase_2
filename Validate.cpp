#include "Validate.h"
#include "ApplicationManager.h"
#include "Start.h"
#include "End.h"
#include "Conditional.h"
#include "Declare.h"
//#include "Read.h"
//#include "Write.h"
#include "Statements\ValueAssign.h"
#include "GUI\Output.h"
#include <string>

Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Validate::ReadActionParameters()
{
}

void Validate::Execute()
{
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Validating Flowchart...");

    int statCount = pManager->GetStatementCount();

    for (int i = 0; i < statCount; ++i)
    {
        Statement* pStat = pManager->GetStatement(i);
        if (!pStat->validate(pManager))
            return;
    }

    pOut->PrintMessage("Validation Successful! Flowchart is valid.");
}