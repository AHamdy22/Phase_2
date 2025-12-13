#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "Actions\..\AddStart.h"
#include "Actions\..\AddDeclare.h"
#include "Actions\..\Select.h"
#include "Actions\..\AddConnectors.h"
#include "Actions\..\Delete.h"
#include "Actions\..\AddConditional.h"
#include "Actions\..\AddEnd.h"
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
	case ADD_CONDITION:
		pAct = new AddConditional(this);
		break;
	case ADD_START:
		pAct = new AddStart(this);
		break;
	case ADD_END:
		pAct = new AddEnd(this);
		break;

	case ADD_VALUE_ASSIGN:
		pAct = new AddValueAssign(this);
		break;

	case ADD_CONNECTOR:
		pAct = new AddConnectors(this);
		break;

	case SELECT:
		pAct = new Select(this);
		break;

	case DEL:
		pAct = new Delete(this);
		break;

	case ADD_DECLARE_VARIABLE:
		pAct = new AddDeclare(this);
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

Connector *ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		const int tolerance = 5;
		Point start = ConnList[i]->getStartPoint();
		Point end = ConnList[i]->getEndPoint();
		int minX = min(start.x, end.x) - tolerance;
		int maxX = max(start.x, end.x) + tolerance;
		int minY = min(start.y, end.y) - tolerance;
		int maxY = max(start.y, end.y) + tolerance;
		if (P.x >= minX && P.x <= maxX && P.y >= minY && P.y <= maxY)
			return ConnList[i];
	}
	return NULL;
}

Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}

void ApplicationManager::SetSelectedConnector(Connector* pStat)
{
	pSelectedConn = pStat;
}

void ApplicationManager::DeleteConnector(Connector* pStat)
{
	for(int i = 0; i < StatCount; i++)
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

void ApplicationManager::DeleteStatement(Statement* pStat)
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

int ApplicationManager::GetStatementCount() const
{
	return StatCount;
}

int ApplicationManager::GetConnectorCount() const
{
	return ConnCount;
}

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

