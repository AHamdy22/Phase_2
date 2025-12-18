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

    bool isValid = true;

    // 1. Check for exactly one Start statement
    int startCount = pManager->GetStartCount();
    if (startCount == 0)
    {
        pOut->PrintMessage("Error: No Start statement found!");
        isValid = false;
    }
    else if (startCount > 1)
    {
        pOut->PrintMessage("Error: Multiple Start statements found!");
        isValid = false;
    }

    // 2. Check for at least one End statement
    int endCount = 0;
    int statCount = pManager->GetStatementCount();
    for (int i = 0; i < statCount; ++i)
    {
        Statement* pStat = pManager->GetStatementByIndex(i);
        if (pStat && pStat->GetType() == "END")
            endCount++;
    }
    if (endCount == 0)
    {
        pOut->PrintMessage("Error: No End statement found!");
        isValid = false;
    }

    // 3. Validate each statement individually
    for (int i = 0; i < statCount; ++i)
    {
        Statement* pStat = pManager->GetStatementByIndex(i);
        if (pStat && !pStat->validate(pManager))
            isValid = false;
    }

    // 4. Final message
    if (isValid)
        pOut->PrintMessage("Validation Successful! Flowchart is valid.");
    else
        pOut->PrintMessage("Validation completed with errors. Please fix them.");
}