//#include "Validate.h"
//#include "ApplicationManager.h"
//#include "Start.h"
//#include "End.h"
//#include "Conditional.h"
//#include "Declare.h"
//#include "Read.h"
//#include "Write.h"
//#include "Statements\ValueAssign.h"
//#include "GUI\Output.h"
//#include <string>
//
//Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager)
//{
//	VarCount = 0;
//}
//
//void Validate::ReadActionParameters()
//{
//	// No parameters to read
//}
//
//void Validate::Execute()
//{
//	Output* pOut = pManager->GetOutput();
//	pOut->PrintMessage("Validating Flowchart...");
//
//	// 1. Basic Structure Validation
//	int startCount = 0;
//	int endCount = 0;
//	int statCount = pManager->GetStatementCount();
//
//	if (statCount == 0)
//	{
//		pOut->PrintMessage("Validation Failed: Flowchart is empty.");
//		return;
//	}
//
//	for (int i = 0; i < statCount; ++i)
//	{
//		Statement* pStat = pManager->GetStatement(i);
//		if (dynamic_cast<Start*>(pStat)) startCount++;
//		if (dynamic_cast<End*>(pStat)) endCount++;
//
//		// Check incoming connections (except Start)
//		if (!dynamic_cast<Start*>(pStat))
//		{
//			if (pStat->getInConnectorCount() == 0)
//			{
//				pOut->PrintMessage("Validation Failed: Statement (ID " + to_string(pStat->GetID()) + ") is unreachable (no incoming connection).");
//				return;
//			}
//		}
//
//		// Check outgoing connections
//		if (!dynamic_cast<End*>(pStat))
//		{
//			Conditional* pCond = dynamic_cast<Conditional*>(pStat);
//			if (pCond)
//			{
//				if (pCond->getOutConnector() == nullptr || pCond->getNoConnector() == nullptr)
//				{
//					pOut->PrintMessage("Validation Failed: Conditional Statement (ID " + to_string(pStat->GetID()) + ") must have both Yes and No branches.");
//					return;
//				}
//			}
//			else
//			{
//				if (pStat->getOutConnector() == nullptr)
//				{
//					pOut->PrintMessage("Validation Failed: Statement (ID " + to_string(pStat->GetID()) + ") has no outgoing connection.");
//					return;
//				}
//			}
//		}
//	}
//
//	if (startCount != 1)
//	{
//		pOut->PrintMessage("Validation Failed: Flowchart must have exactly one Start. Found: " + to_string(startCount));
//		return;
//	}
//	if (endCount != 1)
//	{
//		pOut->PrintMessage("Validation Failed: Flowchart must have exactly one End. Found: " + to_string(endCount));
//		return;
//	}
//
//	// 2. Data Flow Analysis (Variables)
//	BuildCFG();
//	AnalyzeDataFlow();
//
//	// 3. Check usage against computed states
//	for (int i = 0; i < statCount; ++i)
//	{
//		Statement* pStat = pManager->GetStatement(i);
//		string errorMsg;
//		if (!CheckSemantics(pStat, errorMsg))
//		{
//			pOut->PrintMessage("Validation Failed: " + errorMsg);
//			return;
//		}
//	}
//
//	pOut->PrintMessage("Validation Successful! Flowchart is valid.");
//}
//
//int Validate::GetStatementIndex(Statement* pStat)
//{
//	if (!pStat) return -1;
//	int count = pManager->GetStatementCount();
//	for (int i = 0; i < count; ++i)
//	{
//		if (pManager->GetStatement(i) == pStat)
//			return i;
//	}
//	return -1;
//}
//
//void Validate::BuildCFG()
//{
//	int statCount = pManager->GetStatementCount();
//	if (statCount > MaxStats) statCount = MaxStats;
//
//	// Reset counts
//	for (int i = 0; i < statCount; ++i)
//	{
//		AdjCount[i] = 0;
//		RevAdjCount[i] = 0;
//	}
//
//	for (int i = 0; i < statCount; ++i)
//	{
//		Statement* src = pManager->GetStatement(i);
//
//		// Handle Conditional (2 outputs)
//		Conditional* pCond = dynamic_cast<Conditional*>(src);
//		if (pCond)
//		{
//			Connector* yesConn = pCond->getOutConnector();
//			Connector* noConn = pCond->getNoConnector();
//			if (yesConn && yesConn->getDstStat())
//			{
//				int v = GetStatementIndex(yesConn->getDstStat());
//				if (v != -1)
//				{
//					Adj[i][AdjCount[i]++] = v;
//					if (RevAdjCount[v] < MaxIn) RevAdj[v][RevAdjCount[v]++] = i;
//				}
//			}
//			if (noConn && noConn->getDstStat())
//			{
//				int v = GetStatementIndex(noConn->getDstStat());
//				if (v != -1)
//				{
//					Adj[i][AdjCount[i]++] = v;
//					if (RevAdjCount[v] < MaxIn) RevAdj[v][RevAdjCount[v]++] = i;
//				}
//			}
//		}
//		else
//		{
//			// Normal statement
//			Connector* conn = src->getOutConnector();
//			if (conn && conn->getDstStat())
//			{
//				int v = GetStatementIndex(conn->getDstStat());
//				if (v != -1)
//				{
//					Adj[i][AdjCount[i]++] = v;
//					if (RevAdjCount[v] < MaxIn) RevAdj[v][RevAdjCount[v]++] = i;
//				}
//			}
//		}
//	}
//}
//
//int Validate::GetVarIndex(string name)
//{
//	for (int i = 0; i < VarCount; ++i)
//	{
//		if (VarNames[i] == name) return i;
//	}
//	if (VarCount < MaxVars)
//	{
//		VarNames[VarCount] = name;
//		return VarCount++;
//	}
//	return -1; // Table full
//}
//
//void Validate::SetAll(bool dest[], bool val)
//{
//	for (int i = 0; i < MaxVars; ++i) dest[i] = val;
//}
//
//void Validate::SetIntersection(bool dest[], const bool src[])
//{
//	for (int i = 0; i < MaxVars; ++i) dest[i] = dest[i] && src[i];
//}
//
//void Validate::SetCopy(bool dest[], const bool src[])
//{
//	for (int i = 0; i < MaxVars; ++i) dest[i] = src[i];
//}
//
//void Validate::AnalyzeDataFlow()
//{
//	int statCount = pManager->GetStatementCount();
//	if (statCount > MaxStats) statCount = MaxStats;
//
//	// 1. Collect all variables (Universe)
//	VarCount = 0;
//	for (int i = 0; i < statCount; ++i)
//	{
//		Statement* pStat = pManager->GetStatement(i);
//		if (Declare* s = dynamic_cast<Declare*>(pStat)) GetVarIndex(s->getVar());
//		if (Read* s = dynamic_cast<Read*>(pStat)) GetVarIndex(s->getVar());
//		if (Write* s = dynamic_cast<Write*>(pStat)) GetVarIndex(s->getVar());
//		if (ValueAssign* s = dynamic_cast<ValueAssign*>(pStat)) GetVarIndex(s->getLHS());
//		if (Conditional* s = dynamic_cast<Conditional*>(pStat)) {
//			GetVarIndex(s->getLHS());
//			if (s->getVariableRHS() != "") GetVarIndex(s->getVariableRHS());
//		}
//	}
//
//	// 2. Initialize States
//	// Start with Universe (true) for Intersection logic
//	for (int i = 0; i < statCount; ++i)
//	{
//		SetAll(inStates[i].declared, true);
//		SetAll(inStates[i].initialized, true);
//		SetAll(outStates[i].declared, true);
//		SetAll(outStates[i].initialized, true);
//	}
//
//	// Find Start node(s) and set IN to Empty (false)
//	// Start node generates nothing, so its OUT is also Empty initially? 
//	// Actually, Start node IN is Empty. Its OUT depends on Gen. Start Gen is empty.
//	// So Start OUT is Empty.
//	for (int i = 0; i < statCount; ++i)
//	{
//		if (dynamic_cast<Start*>(pManager->GetStatement(i)))
//		{
//			SetAll(inStates[i].declared, false);
//			SetAll(inStates[i].initialized, false);
//			SetAll(outStates[i].declared, false);
//			SetAll(outStates[i].initialized, false);
//		}
//	}
//
//	// 3. Worklist Algorithm
//	// Simple Queue using array
//	int queue[MaxStats * 50];
//	int head = 0;
//	int tail = 0;
//
//	// Initialize queue with all nodes
//	for (int i = 0; i < statCount; ++i)
//	{
//		queue[tail++] = i;
//	}
//
//	int iterLimit = 20000; // Safety break
//	while (head < tail && iterLimit > 0)
//	{
//		iterLimit--;
//		int u = queue[head++];
//
//		// If queue is getting too large, reset (circular) or just rely on large buffer
//		// With 200 nodes, 10000 buffer is plenty.
//
//		Statement* pStat = pManager->GetStatement(u);
//
//		// Calculate In[u] = Intersection(Out[p]) for all p in predecessors
//		State newIn;
//		// Initialize newIn to Universe (true) unless it's Start
//		if (dynamic_cast<Start*>(pStat))
//		{
//			SetAll(newIn.declared, false);
//			SetAll(newIn.initialized, false);
//		}
//		else
//		{
//			SetAll(newIn.declared, true);
//			SetAll(newIn.initialized, true);
//
//			if (RevAdjCount[u] == 0)
//			{
//				// Unreachable? Keep Universe or Empty?
//				// If we want to validate unreachable code strictly:
//				// If it has no preds, it receives nothing.
//				// But we already checked connectivity.
//				// Let's assume Universe to avoid false positives if logic is weird.
//			}
//			else
//			{
//				// Intersect with first predecessor
//				SetCopy(newIn.declared, outStates[RevAdj[u][0]].declared);
//				SetCopy(newIn.initialized, outStates[RevAdj[u][0]].initialized);
//
//				// Intersect with rest
//				for (int k = 1; k < RevAdjCount[u]; ++k)
//				{
//					int pred = RevAdj[u][k];
//					SetIntersection(newIn.declared, outStates[pred].declared);
//					SetIntersection(newIn.initialized, outStates[pred].initialized);
//				}
//			}
//		}
//
//		// Update In[u]
//		SetCopy(inStates[u].declared, newIn.declared);
//		SetCopy(inStates[u].initialized, newIn.initialized);
//
//		// Calculate Out[u] = In[u] U Gen[u]
//		State newOut;
//		SetCopy(newOut.declared, newIn.declared);
//		SetCopy(newOut.initialized, newIn.initialized);
//
//		// Apply Gen
//		if (Declare* s = dynamic_cast<Declare*>(pStat))
//		{
//			int idx = GetVarIndex(s->getVar());
//			if (idx != -1) newOut.declared[idx] = true;
//		}
//		else if (Read* s = dynamic_cast<Read*>(pStat))
//		{
//			int idx = GetVarIndex(s->getVar());
//			if (idx != -1) newOut.initialized[idx] = true;
//		}
//		else if (ValueAssign* s = dynamic_cast<ValueAssign*>(pStat))
//		{
//			int idx = GetVarIndex(s->getLHS());
//			if (idx != -1) newOut.initialized[idx] = true;
//		}
//
//		// Check for change
//		if (newOut != outStates[u])
//		{
//			outStates[u] = newOut;
//			// Add successors to queue
//			for (int k = 0; k < AdjCount[u]; ++k)
//			{
//				int v = Adj[u][k];
//				// Avoid adding duplicates if possible, but simple queue is robust enough
//				queue[tail++] = v;
//				if (tail >= MaxStats * 50) tail = 0; // Wrap around if needed, but risky if head doesn't wrap
//				// Better to just ensure buffer is huge or use % 
//			}
//		}
//
//		if (head >= MaxStats * 50) head = 0; // Wrap head too
//	}
//}
//
//bool Validate::CheckSemantics(Statement* pStat, string& errorMsg)
//{
//	int u = GetStatementIndex(pStat);
//	if (u == -1) return true;
//
//	State& state = inStates[u];
//
//	// Check usages
//	if (Read* s = dynamic_cast<Read*>(pStat))
//	{
//		int idx = GetVarIndex(s->getVar());
//		if (idx != -1 && !state.declared[idx])
//		{
//			errorMsg = "Variable '" + s->getVar() + "' used in Read (ID " + to_string(s->GetID()) + ") but not declared on all paths.";
//			return false;
//		}
//	}
//	else if (Write* s = dynamic_cast<Write*>(pStat))
//	{
//		int idx = GetVarIndex(s->getVar());
//		if (idx != -1)
//		{
//			if (!state.declared[idx])
//			{
//				errorMsg = "Variable '" + s->getVar() + "' used in Write (ID " + to_string(s->GetID()) + ") but not declared on all paths.";
//				return false;
//			}
//			if (!state.initialized[idx])
//			{
//				errorMsg = "Variable '" + s->getVar() + "' used in Write (ID " + to_string(s->GetID()) + ") but not initialized on all paths.";
//				return false;
//			}
//		}
//	}
//	else if (ValueAssign* s = dynamic_cast<ValueAssign*>(pStat))
//	{
//		int idx = GetVarIndex(s->getLHS());
//		if (idx != -1 && !state.declared[idx])
//		{
//			errorMsg = "Variable '" + s->getLHS() + "' assigned in (ID " + to_string(s->GetID()) + ") but not declared on all paths.";
//			return false;
//		}
//	}
//	else if (Conditional* s = dynamic_cast<Conditional*>(pStat))
//	{
//		int idx = GetVarIndex(s->getLHS());
//		if (idx != -1)
//		{
//			if (!state.declared[idx])
//			{
//				errorMsg = "Variable '" + s->getLHS() + "' used in Conditional (ID " + to_string(s->GetID()) + ") but not declared on all paths.";
//				return false;
//			}
//			if (!state.initialized[idx])
//			{
//				errorMsg = "Variable '" + s->getLHS() + "' used in Conditional (ID " + to_string(s->GetID()) + ") but not initialized on all paths.";
//				return false;
//			}
//		}
//
//		if (s->getVariableRHS() != "")
//		{
//			int rhsIdx = GetVarIndex(s->getVariableRHS());
//			if (rhsIdx != -1)
//			{
//				if (!state.declared[rhsIdx])
//				{
//					errorMsg = "Variable '" + s->getVariableRHS() + "' used in Conditional (ID " + to_string(s->GetID()) + ") but not declared on all paths.";
//					return false;
//				}
//				if (!state.initialized[rhsIdx])
//				{
//					errorMsg = "Variable '" + s->getVariableRHS() + "' used in Conditional (ID " + to_string(s->GetID()) + ") but not initialized on all paths.";
//					return false;
//				}
//			}
//		}
//	}
//
//	return true;
//}
