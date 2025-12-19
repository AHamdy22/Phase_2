

#include "Run.h"
#include "ApplicationManager.h"
#include "GUI\Output.h"

Run::Run(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Run::ReadActionParameters()
{
}

void Run::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Running Flowchart...");

	// if validation fails, do not run
	if (!pManager->isValidated())
	{
		pOut->PrintMessage("Error: Flowchart is not validated. Please validate before running.");
		return;
	}

	// get the start statement from
	Statement* startStat = NULL;
	int statCount = pManager->GetStatCount();
	for (int i = 0; i < statCount; i++)
	{
		Statement* pStat = pManager->GetStatement(i);
		if (pStat->GetType() == "START")
		{
			startStat = pStat;
			break;
		}
	}

	/*while (startStat != NULL)
	{
		Connector* outConn = startStat->getOutConnector();
		if (outConn == nullptr)
			break; // no outgoing connector, end of flowchart
		Statement* nextStat = outConn->getDstStat();
		if (nextStat == nullptr)
			break;
		startStat = nextStat;



		startStat->Simulate(pManager);

	}*/

	while (startStat != nullptr)
	{
		startStat->Simulate(pManager);

		if (startStat->GetType() == "CONDITIONAL")
			startStat = pManager->GetNextStatement();
		else
			startStat = startStat->getOutConnector() ? startStat->getOutConnector()->getDstStat() : nullptr;

	}

}
//#include "Run.h"
//#include "ApplicationManager.h"
//#include "GUI\Output.h"
//
//Run::Run(ApplicationManager * pAppManager) : Action(pAppManager)
//{
//}
//
//void Run::ReadActionParameters()
//{
//}
//
//void Run::Execute()
//{ 
//	Output* pOut = pManager->GetOutput();
//	pOut->PrintMessage("Running Flowchart...");
//
//	Validate* validate = new Validate(pManager);
//	validate->Execute();
//
//	// if validation fails, do not run
//	if (!pManager->isValidated())
//	{
//		pOut->PrintMessage("Error: Flowchart is not validated. Please validate before running.");
//		return;
//	}
//
//	// get the start statement from
//	Statement* startStat = NULL;
//	int statCount = pManager->GetStatCount();
//	for (int i = 0; i < statCount; i++)
//	{
//		Statement* pStat = pManager->GetStatement(i);
//		if (pStat->GetType() == "START")
//		{
//			startStat = pStat;
//			break;
//		}
//	}
//
//	while (startStat != NULL)
//	{
//		Connector* outConn = startStat->getOutConnector();
//		if (outConn == nullptr)
//			break; // no outgoing connector, end of flowchart
//		Statement* nextStat = outConn->getDstStat();
//		if (nextStat == nullptr)
//			break;
//		startStat = nextStat;
//
//		startStat->Simulate(pManager);
//
//	}
//}
