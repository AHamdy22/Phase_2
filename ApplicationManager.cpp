#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "Actions\..\AddDeclare.h"
#include "Actions\..\AddVariableAssign.h"
#include "Actions\..\AddOperatorAssign.h"
#include "Actions\..\Select.h"
#include "Actions\..\AddStart.h"
#include "Actions\..\AddConditional.h"
#include "Actions\..\AddEnd.h"
#include "Actions\..\AddWrite.h"
#include "Actions\..\AddRead.h"
#include "Actions\..\Edit.h"
#include "Actions\..\Delete.h"
#include "Actions\..\Copy.h"
#include "Actions\..\Cut.h"
#include "Actions\..\Paste.h"
#include "Actions\..\Run.h"
#include "AddConnectors.h"
#include "Save.h"
#include "Load.h"
#include "Validate.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	VarCount = 0;
	validated = false;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;   //no Connector is selected yet
	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_DECLARE_VARIABLE:
			pAct = new AddDeclare(this);
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVariableAssign(this);
			break;

		case ADD_OPER_ASSIGN:
			pAct = new AddOperatorAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddConditional(this);
			break;

		case ADD_START:
			pAct = new AddStart(this);
			break;

		case ADD_END:
			pAct = new AddEnd(this);
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;

		case ADD_READ:
			pAct = new AddRead(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case EDIT_STAT:
			pAct = new Edit(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case CUT:
			pAct = new Cut(this);
			break;

		case PASTE:
			pAct = new Paste(this);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnectors(this);
			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
			break;

		case VALIDATE:
			pAct = new Validate(this);
			break;

		case SWITCH_SIM_MODE:
			pOut->CreateSimulationToolBar();
			UI.AppMode = SIMULATION;
			break;

		case SWITCH_DSN_MODE:
			pOut->CreateDesignToolBar();
			UI.AppMode = DESIGN;
			break;

		case RUN:
			pAct = new Run(this);
			break;

		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)//upcasting (will get derived classes' objects only)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	
    for (int i = 0; i < StatCount; i++)
    {

        if (StatList[i]->InStatement(P))
            return StatList[i];
    }

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}

Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		const int Range = 5;

		Point start = ConnList[i]->getStartPoint();
		Point end = ConnList[i]->getEndPoint();

		int minX = min(start.x, end.x) - Range;
		int maxX = max(start.x, end.x) + Range;
		int minY = min(start.y, end.y) - Range;
		int maxY = max(start.y, end.y) + Range;

		if (P.x >= minX && P.x <= maxX && P.y >= minY && P.y <= maxY)
			return ConnList[i];
	}
	return NULL;
}

int ApplicationManager::GetStatCount() const
{
	return StatCount;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

Statement* ApplicationManager::GetStatement(int index) const
{
	if (index >= 0 && index < StatCount)
		return StatList[index];
	return NULL;
}

Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

void ApplicationManager::SetSelectedConnector(Connector* pConn)
{
	pSelectedConn = pConn;
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}


void ApplicationManager::DeleteStatement(Statement * pStat)
{
	// Deselect the statement if it's selected
	if (pStat == GetSelectedStatement())
		SetSelectedStatement(NULL);

	// First, delete all connectors associated with this statement
	for (int i = 0; i < ConnCount; )
	{
		if (ConnList[i]->getSrcStat() == pStat || ConnList[i]->getDstStat() == pStat)
		{
			if (ConnList[i] == GetSelectedConnector())
				SetSelectedConnector(NULL);
				DeleteConnector(ConnList[i]);
		}
		else
		{
			i++;
		}
	}
	// Now, delete the statement itself
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == pStat)
		{
			delete StatList[i];

			for (int j = i; j < StatCount - 1; j++)
				StatList[j] = StatList[j + 1];

			StatCount--;
			break;
		}

	}
	
	// Finally, update GUI
	UpdateInterface();
}

void ApplicationManager::DeleteConnector(Connector* pStat)
{
	for (int i = 0; i < StatCount; i++)
	{
		Connector* outConn = StatList[i]->getOutConnector();
		if (outConn == pStat)
			StatList[i]->setOutConnector(NULL);
	}
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pStat)
		{
			delete ConnList[i];
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[ConnCount - 1] = NULL;
			ConnCount--;
			break;
		}
	}
}

Connector* ApplicationManager::GetConnector(int index) const
{
	if (index >= 0 && index < ConnCount)
		return ConnList[index];
	return nullptr;
}
	
int ApplicationManager::GetConnectorCount() const
{
	return ConnCount;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)

			StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}

void ApplicationManager::setValidated(bool val)
{
	validated = val;
}

bool ApplicationManager::isValidated() const
{
	return validated;
}

int ApplicationManager::GetStartCount() const
{
	int count = 0;
	for (int i = 0; i < StatCount; i++)
		if (StatList[i] && StatList[i]->GetType() == "START")
			count++;
	return count;
}

int ApplicationManager::GetEndCount() const
{
	int count = 0;
	for (int i = 0; i < StatCount; i++)
		if (StatList[i] && StatList[i]->GetType() == "END")
			count++;
	return count;
}

void ApplicationManager::ClearAll()
{
	//Clear statements
	for (int i = 0; i < StatCount; i++)
	{
		delete StatList[i];
		StatList[i] = nullptr;
	}
	StatCount = 0;
	//Clear connectors
	for (int i = 0; i < ConnCount; i++)
	{
		delete ConnList[i];
		ConnList[i] = nullptr;
	}
	ConnCount = 0;
	UpdateInterface();
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeclareVariable(string varName)
{
	// Check if already exists
	int index = FindVariable(varName);

	if (index == -1)  // Variable doesn't exist, add it
	{
		if (VarCount < MaxCount)
		{
			VarList[VarCount].VarName = varName;
			VarList[VarCount].IsDeclared = true;
			VarList[VarCount].IsInitialized = false;
			VarCount++;
		}
	}

}
void ApplicationManager::SetVariableValue(string varName, double value)
{
	int index = FindVariable(varName);

	if (index != -1)
	{
		VarList[index].Value = value;
		VarList[index].IsInitialized = true;
	}
}

double ApplicationManager::GetVariableValue(string varName)
{
	int index = FindVariable(varName);

	if (index != -1)
	{
		if (VarList[index].IsInitialized)
		{
			return VarList[index].Value;
		}
	}
	else
		return 0; // Variable not found or not initialized
}

bool ApplicationManager::IsVariableDeclared(string varName)
{
	int index = FindVariable(varName);

	if (index != -1)
		return VarList[index].IsDeclared;

	return false;
}
bool ApplicationManager::IsVariableInitialized(string varName)
{
	int index = FindVariable(varName);

	if (index != -1)
		return //VarList[index].IsDeclared &&
		VarList[index].IsInitialized;

	return false;
}
int ApplicationManager::FindVariable(string varName)
{
	for (int i = 0; i < VarCount; i++)
	{
		if (VarList[i].VarName == varName)
			return i;
	}
	return -1;  // Variable not found
}

void ApplicationManager::SetVariableInitialized(string varName, bool initialized)
{
	int index = FindVariable(varName);

	if (index != -1)
	{
		VarList[index].IsInitialized = initialized;
	}
}
//void ApplicationManager::RemoveVariable(string varName)
//{
//	int index = FindVariable(varName);
//
//	if (index != -1)  // Variable found
//	{
//		// Shift all variables after this one to the left
//		for (int i = index; i < VarCount - 1; i++)
//		{
//			VarList[i] = VarList[i + 1];
//		}
//
//		// Clear the last element
//		VarList[VarCount - 1].VarName = "";
//		VarList[VarCount - 1].Value = 0.0;
//		VarList[VarCount - 1].IsDeclared = false;
//		VarList[VarCount - 1].IsInitialized = false;
//
//		// Decrement count
//		VarCount--;
//	}
//}
void ApplicationManager::SetNextStatement(Statement* pStat)
{
	pNextStat = pStat;
}

Statement* ApplicationManager::GetNextStatement() const
{
	return pNextStat;
}

void ApplicationManager::ClearVariables()
{
	VarCount = 0;
	// Reset all variables
	for (int i = 0; i < MaxCount; i++)
	{
		VarList[i].VarName = "";
		VarList[i].IsDeclared = false;
		VarList[i].IsInitialized = false;
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
