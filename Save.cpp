#include "Save.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <fstream>

Save::Save(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Save::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Save Flowchart: Enter the file name to save the flowchart: ");
    FileName = pIn->GetString(pOut);
    FileName += ".txt"; // Add .txt extension
    pOut->ClearStatusBar();
}

void Save::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    ofstream outFile(FileName);

    if (!outFile.is_open())
    {
        pOut->PrintMessage("Error: Cannot create file " + FileName);
        return;
    }

    // Save number of statements
    int statCount = pManager->GetStatementCount();
    outFile << statCount << endl;

    // Save each statement
    for (int i = 0; i < statCount; i++)
    {
        Statement* pStat = pManager->GetStatement(i);
        if (pStat != nullptr)
        {
            pStat->Save(outFile);
        }
    }

    // Save number of connectors
    int connCount = pManager->GetConnectorCount();
    outFile << connCount << endl;

    // Save each connector
    for (int i = 0; i < connCount; i++)
    {
        Connector* pConn = pManager->GetConnector(i);
        if (pConn != nullptr)
        {
            pConn->Save(outFile);
        }
    }

    outFile.close();
    pOut->PrintMessage("Flowchart saved successfully to " + FileName);
}