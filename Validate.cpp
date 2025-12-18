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

	int startCount = 0;
	int endCount = 0;
	int statCount = pManager->GetStatementCount();

	if (statCount == 0)
	{
		pOut->PrintMessage("Validation Failed: Flowchart is empty.");
		return;
	}

	for (int i = 0; i < statCount; ++i)
	{
		Statement* pStat = pManager->GetStatement(i);
		if (dynamic_cast<Start*>(pStat)) startCount++;
		else if (dynamic_cast<End*>(pStat)) endCount++;
		//else if (dynamic_cast<Read*>(pStat)) pStat->validate(pManager);
		//else if (dynamic_cast<Write*>(pStat)) pStat->validate(pManager);
		else if (dynamic_cast<ValueAssign*>(pStat)) pStat->validate(pManager);
		else if (dynamic_cast<Declare*>(pStat)) pStat->validate(pManager);
		else if (dynamic_cast<Conditional*>(pStat)) pStat->validate(pManager);
	}

	if (startCount != 1)
	{
		pOut->PrintMessage("Validation Failed: Flowchart must have exactly one Start.");
		return;
	}
	if (endCount != 1)
	{
		pOut->PrintMessage("Validation Failed: Flowchart must have exactly one End.");
		return;
	}

	pOut->PrintMessage("Validation Successful! Flowchart is valid.");
}