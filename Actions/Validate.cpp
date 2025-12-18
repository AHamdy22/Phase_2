#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\Start.h"
#include "..\End.h"
#include "..\Conditional.h"
#include "..\GUI\Output.h"

Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Validate::ReadActionParameters()
{
	// No parameters to read
}

void Validate::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Validating Flowchart...");

	// 1. Reset Global State (Variables)
	pManager->ClearVariables();

	// 2. Structural Checks (Start/End Count)
	int startCount = 0;
	int endCount = 0;
	int statCount = pManager->GetStatementCount();
	Statement* pStart = nullptr;

	if (statCount == 0)
	{
		pOut->PrintMessage("Validation Failed: Flowchart is empty.");
		return;
	}

	for (int i = 0; i < statCount; ++i)
	{
		Statement* pStat = pManager->GetStatement(i);
		if (dynamic_cast<Start*>(pStat))
		{
			startCount++;
			pStart = pStat;
		}
		if (dynamic_cast<End*>(pStat)) endCount++;
	}

	if (startCount != 1)
	{
		pOut->PrintMessage("Validation Failed: Must have exactly one Start. Found: " + to_string(startCount));
		return;
	}
	if (endCount != 1)
	{
		pOut->PrintMessage("Validation Failed: Must have exactly one End. Found: " + to_string(endCount));
		return;
	}

	// 3. Traversal and Validation
	// Simple BFS to visit nodes in flow order
	bool visited[200]; // MaxCount is 200
	for (int i = 0; i < 200; ++i) visited[i] = false;

	Statement* queue[200];
	int head = 0, tail = 0;

	// Push Start node
	if (pStart)
	{
		queue[tail++] = pStart;
		int idx = GetStatementIndex(pStart);
		if (idx != -1) visited[idx] = true;
	}

	while (head < tail)
	{
		Statement* curr = queue[head++];
		
		// Validate the current statement using its own validate method
		if (!curr->validate(pManager))
		{
			// validate() prints the error message to pOut
			return; 
		}

		// Add neighbors to queue
		Conditional* pCond = dynamic_cast<Conditional*>(curr);
		if (pCond)
		{
			Connector* yes = pCond->getOutConnector(); // Yes connector
			if (yes && yes->getDstStat())
			{
				Statement* dst = yes->getDstStat();
				int idx = GetStatementIndex(dst);
				if (idx != -1 && !visited[idx])
				{
					visited[idx] = true;
					queue[tail++] = dst;
				}
			}
			
			Connector* no = pCond->getNoConnector(); // No connector
			if (no && no->getDstStat())
			{
				Statement* dst = no->getDstStat();
				int idx = GetStatementIndex(dst);
				if (idx != -1 && !visited[idx])
				{
					visited[idx] = true;
					queue[tail++] = dst;
				}
			}
		}
		else
		{
			// Normal statement
			Connector* conn = curr->getOutConnector();
			if (conn && conn->getDstStat())
			{
				Statement* dst = conn->getDstStat();
				int idx = GetStatementIndex(dst);
				if (idx != -1 && !visited[idx])
				{
					visited[idx] = true;
					queue[tail++] = dst;
				}
			}
		}
	}

	// Check for unreachable statements?
	// If we want to strictly validate that all statements are reachable:
	/*
	for(int i=0; i<statCount; ++i) {
		if(!visited[i]) {
			pOut->PrintMessage("Warning: Statement ID " + to_string(pManager->GetStatement(i)->GetID()) + " is unreachable.");
			// return; // Optional
		}
	}
	*/

	pOut->PrintMessage("Validation Successful! Flowchart is valid.");
}

int Validate::GetStatementIndex(Statement* pStat)
{
	int count = pManager->GetStatementCount();
	for (int i = 0; i < count; ++i)
	{
		if (pManager->GetStatement(i) == pStat) return i;
	}
	return -1;
}
