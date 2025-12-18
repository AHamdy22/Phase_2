#include "Load.h"
#include "ApplicationManager.h"
#include "GUI/input.h"
#include "GUI/Output.h"
#include "Read.h"
#include "Write.h"
#include "Start.h"
#include "End.h"
#include "Declare.h"
#include "Conditional.h"
#include "Statements\ValueAssign.h"
#include "VariableAssign.h"
#include "OperatorAssign.h"
#include <fstream>

Load::Load(ApplicationManager* pAppManager) : Action(pAppManager) 
{}

void Load::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Load Flowchart: Enter the file name to load: ");
    FileName = pIn->GetString(pOut);
    FileName += ".txt";
    pOut->ClearStatusBar();
}

void Load::Execute()
{
    ReadActionParameters();

    ifstream InFile(FileName);
    Output* pOut = pManager->GetOutput();

    if (!InFile.is_open())
    {
        pOut->PrintMessage("Error: Could not open file " + FileName);
        return;
    }

    // TODO: Clear existing flowchart first
    pManager->ClearAll();

    // Read number of statements
    int StatementCount;
    InFile >> StatementCount;

    // Temporary array to store loaded statements
    Statement* StatList[200];
    for (int i = 0; i < 200; i++)
        StatList[i] = nullptr;

    // Load each statement
    for (int i = 0; i < StatementCount; i++)
    {
        string StatementType;
        InFile >> StatementType;

        Statement* pStat = nullptr;

        if (StatementType == "VALUE_ASSIGN")
        {
            int id;
            int x, y;
            string lhs;
            double rhs;
            InFile >> id >> x >> y >> lhs >> rhs;

            Point corner(x, y);
            pStat = new ValueAssign(corner, lhs, rhs);
            pStat->SetID(id);
        }

        else if (StatementType == "VARIABLE_ASSIGN")
        {
            int id;
            int x, y;
            string lhs;
            string rhs;
            InFile >> id >> x >> y >> lhs >> rhs;

            Point corner(x, y);
            pStat = new VariableAssign(corner, lhs, rhs);
            pStat->SetID(id);
        }

        else if (StatementType == "OPERATOR_ASSIGN")
        {
            int id;
            int x, y;
            string lhs, op1, op2;
            char operation;

            InFile >> id >> x >> y >> lhs >> op1 >> operation >> op2;

            Point corner(x, y);

            // Determine operands
            double valOp1 = 0, valOp2 = 0;
            string varOp1 = "", varOp2 = "";

            if (IsValue(op1))
                valOp1 = stod(op1);
            else
                varOp1 = op1;

            if (IsValue(op2))
                valOp2 = stod(op2);
            else
                varOp2 = op2;

            pStat = new OperatorAssign(corner, lhs, valOp1, varOp1, valOp2, varOp2, operation);
            pStat->SetID(id);
        }

        else if (StatementType == "READ")
        {
            int id;
            int x, y;
            string varName;
            InFile >> id >> x >> y >> varName;

            Point corner(x, y);
            pStat = new Read(corner, varName);
            pStat->SetID(id);
        }
        else if (StatementType == "WRITE")
        {
            int id;
            int x, y;
            string varName;
            InFile >> id >> x >> y >> varName;

            Point corner(x, y);
            pStat = new Write(corner, varName);
            pStat->SetID(id);
        }
        else if (StatementType == "START")
        {
            int id;
            int x, y;
            InFile >> id >> x >> y;

            Point corner(x, y);
            pStat = new Start(corner);
            pStat->SetID(id);
        }
        else if (StatementType == "END")
        {
            int id;
            int x, y;
            InFile >> id >> x >> y;

            Point corner(x, y);
            pStat = new End(corner);
            pStat->SetID(id);
        }
        else if (StatementType == "DECLARE")
        {
            int id;
            int x, y;
            string dataType, var;
            InFile >> id >> x >> y >> dataType >> var;

            Point corner(x, y);
            pStat = new Declare(corner, dataType, var);
            pStat->SetID(id);
        }
        else if (StatementType == "COND")
        {
            int id;
            int x, y;
            string lhs, op, varRHS;
            double valRHS;
            InFile >> id >> x >> y >> lhs >> op >> valRHS >> varRHS;

            Point corner(x, y);
            if (varRHS == "0")
                pStat = new Conditional(corner, lhs, valRHS, "", op);
            else
                pStat = new Conditional(corner, lhs, 0, varRHS, op);
            pStat->SetID(id);
        }

        if (pStat != nullptr)
        {
            StatList[i] = pStat;
            pManager->AddStatement(pStat);
        }
    }

    // Read number of connectors
    int ConnectorCount;
    InFile >> ConnectorCount;

    // Load each connector
    for (int i = 0; i < ConnectorCount; i++)
    {
        int srcID, dstID, branch;
        InFile >> srcID >> dstID >> branch;

        // Find source and destination statements
        Statement* srcStat = nullptr;
        Statement* dstStat = nullptr;

        for (int j = 0; j < StatementCount; j++)
        {
            if (StatList[j] != nullptr)
            {
                if (StatList[j]->GetID() == srcID)
                    srcStat = StatList[j];
                if (StatList[j]->GetID() == dstID)
                    dstStat = StatList[j];
            }
        }

        if (srcStat != nullptr && dstStat != nullptr)
        {
			Conditional* condStat = dynamic_cast<Conditional*>(srcStat);
			if (condStat != nullptr)
			{
				// Conditional statement
				if (branch == 1 && condStat->getOutConnector() == nullptr)
				{
					// Yes branch
					Connector* pConn = new Connector(srcStat, dstStat);
					pConn->setStartPoint(condStat->getYesOutlet());
					pConn->setEndPoint(dstStat->getInlet());
					pConn->setOutletBranch(branch);
					condStat->setOutConnector(pConn);
					dstStat->addInConnector(pConn);
					pManager->AddConnector(pConn);
					continue;
				}
				else if (branch == 2 && condStat->getNoConnector() == nullptr)
				{
					// No branch
					Connector* pConn = new Connector(srcStat, dstStat);
					pConn->setStartPoint(condStat->getNoOutlet());
					pConn->setEndPoint(dstStat->getInlet());
					pConn->setOutletBranch(branch);
					condStat->setNoConnector(pConn);
					dstStat->addInConnector(pConn);
					pManager->AddConnector(pConn);
					continue;
				}
			}
            else {
                Connector* pConn = new Connector(srcStat, dstStat);
                pConn->setStartPoint(srcStat->getOutlet());
                pConn->setEndPoint(dstStat->getInlet());
                pConn->setOutletBranch(branch);

                srcStat->setOutConnector(pConn);
                dstStat->addInConnector(pConn);
                pManager->AddConnector(pConn);
            }
        }
    }

    InFile.close();
    pOut->PrintMessage("Flowchart loaded successfully from " + FileName);
    pManager->UpdateInterface();
}