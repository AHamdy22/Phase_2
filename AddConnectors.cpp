#include "AddConnectors.h"
#include "ApplicationManager.h"
#include "Conditional.h"
#include "End.h"
#include "Start.h"
#include "GUI\input.h"
#include "GUI\Output.h"

AddConnectors::AddConnectors(ApplicationManager* pAppManager) :Action(pAppManager)
{
	pConn = nullptr;
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
	End* endStat = dynamic_cast<End*>(SrcStat);
	Start* startStat = dynamic_cast<Start*>(DstStat);
	// Validate that both statements exist
	if (SrcStat == nullptr || endStat != nullptr)
	{
		pOut->PrintMessage("Error: No source statement found at the clicked position.");
		return;
	}

	if (DstStat == nullptr || startStat != nullptr)
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

	// Check if the source statement is a Conditional statement
	Conditional* condStat = dynamic_cast<Conditional*>(SrcStat);

	if (condStat != nullptr)
	{
		// Handle Conditional Statement Connectors

		// Check if both connectors already exist
		if (condStat->getOutConnector() != nullptr && condStat->getNoConnector() != nullptr)
		{
			pOut->PrintMessage("Error: Conditional statement already has both Yes and No connectors.");
			return;
		}

		// Ask user which branch (Yes or No)
		pOut->PrintMessage("Is this the Yes branch? (y/n)");
		Input* pIn = pManager->GetInput();
		string response = pIn->GetString(pOut);
		pOut->ClearStatusBar();

		bool isYesBranch = (response == "y" || response == "Y" || response == "yes" || response == "Yes");

		// Get the outlets from conditional
		Point yesOutlet = condStat->getYesOutlet();
		Point noOutlet = condStat->getNoOutlet();

		if (isYesBranch)
		{
			// Yes branch (right side)
			if (condStat->getOutConnector() != nullptr)
			{
				pOut->PrintMessage("Error: Conditional statement already has a Yes connector.");
				return;
			}

			// If No branch already exists, align with it
			if (condStat->getNoConnector() != nullptr)
			{
				Statement* noDestStat = condStat->getNoConnector()->getDstStat();
				if (noDestStat != nullptr)
				{
					Point noDestInlet = noDestStat->getInlet();
					Point dstInlet = DstStat->getInlet();

					// Calculate movements to align both horizontally and vertically
					// 1. Vertical alignment: same Y level as No branch destination
					int deltaY = noDestInlet.y - dstInlet.y;

					// 2. Horizontal alignment: position to the right of conditional
					int desiredX = yesOutlet.x + 100; // 100 pixels to the right
					int deltaX = desiredX - dstInlet.x;

					// Move the Yes destination statement
					DstStat->Move(deltaX, deltaY);
				}
			}
			else
			{
				// No branch doesn't exist yet - just position below and to the right
				Point dstInlet = DstStat->getInlet();

				// Position 100 pixels to the right and 100 pixels below conditional
				int desiredX = yesOutlet.x + 100;
				int desiredY = yesOutlet.y + 100;

				int deltaX = desiredX - dstInlet.x;
				int deltaY = desiredY - dstInlet.y;

				DstStat->Move(deltaX, deltaY);
			}

			// Create the connector
			pConn = new Connector(condStat, DstStat);
			pConn->setOutletBranch(1); // 1 for Yes branch

			// Set start and end points
			pConn->setStartPoint(condStat->getYesOutlet());
			pConn->setEndPoint(DstStat->getInlet());

			// Update the statements
			condStat->setOutConnector(pConn);
			DstStat->addInConnector(pConn);
		}
		else
		{
			// No branch (left side)
			if (condStat->getNoConnector() != nullptr)
			{
				pOut->PrintMessage("Error: Conditional statement already has a No connector.");
				return;
			}

			// If Yes branch already exists, align with it
			if (condStat->getOutConnector() != nullptr)
			{
				Statement* yesDestStat = condStat->getOutConnector()->getDstStat();
				if (yesDestStat != nullptr)
				{
					Point yesDestInlet = yesDestStat->getInlet();
					Point dstInlet = DstStat->getInlet();

					// Calculate movements to align both horizontally and vertically
					// 1. Vertical alignment: same Y level as Yes branch destination
					int deltaY = yesDestInlet.y - dstInlet.y;

					// 2. Horizontal alignment: position to the left of conditional
					int desiredX = noOutlet.x - 100; // 100 pixels to the left
					int deltaX = desiredX - dstInlet.x;

					// Move the No destination statement
					DstStat->Move(deltaX, deltaY);
				}
			}
			else
			{
				// Yes branch doesn't exist yet - just position below and to the left
				Point dstInlet = DstStat->getInlet();

				// Position 100 pixels to the left and 100 pixels below conditional
				int desiredX = noOutlet.x - 100;
				int desiredY = noOutlet.y + 100;

				int deltaX = desiredX - dstInlet.x;
				int deltaY = desiredY - dstInlet.y;

				DstStat->Move(deltaX, deltaY);
			}

			// Create the connector
			pConn = new Connector(condStat, DstStat);
			pConn->setOutletBranch(2); // 2 for No branch

			// Set start and end points
			pConn->setStartPoint(condStat->getNoOutlet());
			pConn->setEndPoint(DstStat->getInlet());

			// Update the statements
			condStat->setNoConnector(pConn);
			DstStat->addInConnector(pConn);
		}

		// Add the connector to application manager's connector list
		pManager->AddConnector(pConn);

		// Update the interface
		pManager->UpdateInterface();

		pOut->PrintMessage("Connector added successfully.");
	}
	else
	{
		// Handle Normal Statement Connectors

		// Check if source statement already has an outgoing connector
		if (SrcStat->getOutConnector() != nullptr)
		{
			pOut->PrintMessage("Error: Source statement already has an outgoing connector.");
			return;
		}

		// Handling if the DstStat is positioned above the SrcStat
		else if (DstStat->getLeftCornerY() <= SrcStat->getLeftCornerY() + 50)
		{
			// Get outlet and inlet points
			Point srcOutlet = SrcStat->getOutlet();
			Point dstInlet = DstStat->getInlet();

			// Calculate horizontal difference to align centers
			int deltaX = srcOutlet.x - dstInlet.x;

			// Calculate vertical difference
			int deltaY = srcOutlet.y - dstInlet.y;

			// Move destination statement to align with source
			if (deltaX != 0)
			{
				DstStat->Move(deltaX, deltaY + 30);
				// Update inlet after moving
				dstInlet = DstStat->getInlet();
			}

			// Create the connector
			pConn = new Connector(SrcStat, DstStat);
			pConn->setOutletBranch(0); // 0 for normal connector

			// Set the start and end points
			pConn->setStartPoint(srcOutlet);
			pConn->setEndPoint(dstInlet);

			// Update the statements to reference this connector
			SrcStat->setOutConnector(pConn);
			DstStat->addInConnector(pConn);

			// Add the connector to application manager's connector list
			pManager->AddConnector(pConn);

			// Update the interface
			pManager->UpdateInterface();

			pOut->PrintMessage("Connector added successfully.");
		}

		else
		{
			// Get outlet and inlet points
			Point srcOutlet = SrcStat->getOutlet();
			Point dstInlet = DstStat->getInlet();

			// Calculate horizontal difference to align centers
			int deltaX = srcOutlet.x - dstInlet.x;

			// Move destination statement to align with source
			if (deltaX != 0)
			{
				DstStat->Move(deltaX, 0);
				// Update inlet after moving
				dstInlet = DstStat->getInlet();
			}

			// Create the connector
			pConn = new Connector(SrcStat, DstStat);
			pConn->setOutletBranch(0); // 0 for normal connector

			// Set the start and end points
			pConn->setStartPoint(srcOutlet);
			pConn->setEndPoint(dstInlet);

			// Update the statements to reference this connector
			SrcStat->setOutConnector(pConn);
			DstStat->addInConnector(pConn);

			// Add the connector to application manager's connector list
			pManager->AddConnector(pConn);

			// Update the interface
			pManager->UpdateInterface();

			pOut->PrintMessage("Connector added successfully.");
		}
	}
}