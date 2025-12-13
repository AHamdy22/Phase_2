#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "AddConditional.h"
#include "AddDeclare.h"
#include "AddConnectors.h"
#include "Save.h"
#include "Load.h"
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
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i = 0; i < MaxCount; i++)
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
		case ADD_START:
			pAct = new AddStart(this);
			break;

		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddConditional(this);
			break;

		case ADD_READ:
			pAct = new AddRead(this);
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;

		case ADD_END:
			pAct = new AddEnd(this);
			break;

		case ADD_DECLARE_VARIABLE:
			pAct = new AddDeclare(this);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnectors(this);
			break;


		case SELECT:
			///create Select Action here

			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
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
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

Statement* ApplicationManager::GetStatement(int index) const
{
	if (index >= 0 && index < StatCount)
		return StatList[index];
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////

	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities
	
	


Statement* ApplicationManager::GetStatement(Point p) const
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] != nullptr && StatList[i]->InStatement(p))
		{
			return StatList[i];
		}
	}
	return nullptr;
}

int ApplicationManager::GetStatementCount() const
{
	return StatCount;
}

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
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


////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}


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
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
