#include "AddConnectors.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"

AddConnectors::AddConnectors(ApplicationManager* pAppManager) :Action(pAppManager)
{
	pConn = nullptr;  // Initialize pointer to null
}


void AddConnectors::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (StartPoint) parameter
	pOut->PrintMessage("Connector: Click on the source statement to connect from");
	pIn->GetPointClicked(StartPoint);
	pOut->ClearStatusBar();

	//Read the (EndPoint) parameter
	pOut->PrintMessage("Connector: Click on the destination statement to connect to");
	pIn->GetPointClicked(EndPoint);
	pOut->ClearStatusBar();
}

void AddConnectors::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	// Get source and destination statements based on clicked points
	Statement* SrcStat = pManager->GetStatement(StartPoint);
	Statement* DstStat = pManager->GetStatement(EndPoint);

	// Validate that both statements exist
	if (SrcStat == nullptr)
	{
		pOut->PrintMessage("Error: No source statement found at the clicked position.");
		return;
	}

	if (DstStat == nullptr)
	{
		pOut->PrintMessage("Error: No destination statement found at the clicked position.");
		return;
	}

	// Check if source and destination are the same
	if (SrcStat == DstStat)
	{
		pOut->PrintMessage("Error: Cannot connect a statement to itself.");
		return;
	}

	// Check if source statement already has an outgoing connector
	if (SrcStat->getOutConnector() != nullptr)
	{
		pOut->PrintMessage("Error: Source statement already has an outgoing connector.");
		return;
	}

	// Move destination statement to align with source
	Point srcOutlet = SrcStat->getOutlet();
	Point dstInlet = DstStat->getInlet();

	// Calculate horizontal difference in distance to align centers
	int deltaX = srcOutlet.x - dstInlet.x;

	if (deltaX != 0)
	{
		DstStat->Move(deltaX, 0);
	}

	// Create the connector
	pConn = new Connector(SrcStat, DstStat);

	// Set the start and end points of the connector based on statement outlets/inlets
	pConn->setStartPoint(SrcStat->getOutlet());
	pConn->setEndPoint(DstStat->getInlet());

	// Update the statements to reference this connector
	SrcStat->setOutConnector(pConn);
	DstStat->addInConnector(pConn);

	// Add the connector to application manager's connector list
	pManager->AddConnector(pConn);

	pOut->PrintMessage("Connector added successfully.");
}
