#include "Validate.h"
#include "ApplicationManager.h"
#include "GUI\Output.h"

Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager)
{
    pAppManager->ClearVariables();
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

    // 2. Check for exactly one End statement
    int endCount = pManager->GetEndCount();
    if (endCount == 0)
    {
        pOut->PrintMessage("Error: No End statement found!");
        isValid = false;
    }
    else if (endCount > 1)
    {
        pOut->PrintMessage("Error: Multiple End statements found!");
        isValid = false;
    }

    //int statCount = pManager->GetStatCount();

    // get the start statement from
    Statement* startStat = NULL;
    int statCount = pManager->GetStatementCount();
    for (int i = 0; i < statCount; i++)
    {
        Statement* pStat = pManager->GetStatement(i);
        if (pStat->GetType() == "START")
        {
            startStat = pStat;
            break;
        }
    }

    while (startStat != NULL)
    {
        Connector* outConn = startStat->getOutConnector();

        if (outConn == nullptr)
        {
            if (startStat->GetType() != "END")
            {
                pOut->PrintMessage("Error: A statement has no outgoing connector.");
                isValid = false;
                break; // no outgoing connector, end of flowchart
            }
        }
        Statement* nextStat = NULL;
        if (outConn)
        {
            nextStat = outConn->getDstStat();
            startStat = nextStat;
        }
        // if (nextStat == nullptr)
         //{
             //pOut->PrintMessage("Error: A connector has no destination statement.");
             //isValid = false;
             //break;
         //}

        if (nextStat)
        {
            bool isvalidated = nextStat->validate(pManager);
            if (!isvalidated)
            {
                isValid = false;
                break;
            }
        }

        if (nextStat->GetType() == "END")
            break;
    }
    //// 3. Validate each statement individually
    //for (int i = 0; i < statCount; ++i)
    //{
    //    Statement* pStat = pManager->GetStatement(i);
    //    if (pStat && !pStat->Validate(pManager))
    //        isValid = false;
    //}

    // 4. Final message
    if (isValid)
        pOut->PrintMessage("Validation Successful! Flowchart is valid.");

    pManager->setValidated(isValid);
}



//#include "Validate.h"
//#include "ApplicationManager.h"
//#include "GUI\Output.h"
//
//Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager)
//{
//    pAppManager->ClearVariables();
//}
//
//void Validate::ReadActionParameters()
//{
//}
//
//void Validate::Execute()
//{
//    Output* pOut = pManager->GetOutput();
//    pOut->PrintMessage("Validating Flowchart...");
//
//    bool isValid = true;
//
//    // 1. Check for exactly one Start statement
//    int startCount = pManager->GetStartCount();
//    if (startCount == 0)
//    {
//        pOut->PrintMessage("Error: No Start statement found!");
//        isValid = false;
//    }
//    else if (startCount > 1)
//    {
//        pOut->PrintMessage("Error: Multiple Start statements found!");
//        isValid = false;
//    }
//
//    // 2. Check for exactly one End statement
//    int endCount = pManager->GetEndCount();
//    if (endCount == 0)
//    {
//        pOut->PrintMessage("Error: No End statement found!");
//        isValid = false;
//    }
//    else if (endCount > 1)
//    {
//        pOut->PrintMessage("Error: Multiple End statements found!");
//        isValid = false;
//    }
//
//    //int statCount = pManager->GetStatCount();
//
//    // get the start statement from
//    Statement* startStat = NULL;
//    int statCount = pManager->GetStatementCount();
//    for (int i = 0; i < statCount; i++)
//    {
//        Statement* pStat = pManager->GetStatement(i);
//        if (pStat->GetType() == "START")
//        {
//            startStat = pStat;
//            break;
//        }
//    }
//
//    while (startStat != NULL)
//    {
//        Connector* outConn = startStat->getOutConnector();
//        if (outConn == nullptr)
//            break; // no outgoing connector, end of flowchart
//        Statement* nextStat = outConn->getDstStat();
//        if (nextStat == nullptr)
//            break;
//        startStat = nextStat;
//        startStat->validate(pManager);
//    }
//
//    // 4. Final message
//    if (isValid)
//        pOut->PrintMessage("Validation Successful! Flowchart is valid.");
//
//    pManager->setValidated(isValid);
//}