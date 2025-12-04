#include "AddConnector.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
using namespace std;

AddConnector::AddConnector(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void AddConnector::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (StartPoint) parameter
	pOut->PrintMessage("Connector: Click to set the start point of the connector");
	pIn->GetPointClicked(StartPoint);
	pOut->ClearStatusBar();
	//Read the (EndPoint) parameter
	pOut->PrintMessage("Connector: Click to set the end point of the connector");
	pIn->GetPointClicked(EndPoint);
	pOut->ClearStatusBar();
}

void AddConnector::Execute()
{
	ReadActionParameters();
	//Get the source and destination statements based on the clicked points
	Statement* pSrcStat = pManager->GetStatement(StartPoint);
	Statement* pDstStat = pManager->GetStatement(EndPoint);
	//Validate the source and destination statements
	if (pSrcStat == nullptr || pDstStat == nullptr)
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error: Invalid source or destination statement for the connector.");
		return;
	}
	//Create a new connector
	Connector* pConn = new Connector(pSrcStat, pDstStat);
	//Set the start and end points of the connector
	pConn->setStartPoint(StartPoint);
	pConn->setEndPoint(EndPoint);
	//Add the connector to the application manager
	pManager->AddConnector(pConn);
}
