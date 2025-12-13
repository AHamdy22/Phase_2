#include "Connector.h"
#include <fstream>
#include"Statements\Statement.h"
#include "Conditional.h"

Connector::Connector(Statement* Src, Statement* Dst)
{
	OutletBranch = 0;
	Selected = false;
	SrcStat = Src;
	DstStat = Dst;

	Start.x = 0;
	Start.y = 0;
	End.x = 0;
	End.y = 0;
}

void Connector::setSrcStat(Statement* Src)
{
	SrcStat = Src;
}

Statement* Connector::getSrcStat()
{
	return SrcStat;
}

void Connector::setDstStat(Statement* Dst)
{
	DstStat = Dst;
}

Statement* Connector::getDstStat()
{
	return DstStat;
}

bool Connector::IsSelected()
{
	return Selected;
}

void Connector::setStartPoint(Point P)
{
	Start = P;
}

Point Connector::getStartPoint()
{
	return Start;
}

void Connector::setEndPoint(Point P)
{
	End = P;
}

Point Connector::getEndPoint()
{
	return End;
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

void Connector::Draw(Output* pOut) const
{
	if (SrcStat == nullptr || DstStat == nullptr)
	{
		return;  // Don't draw if statements don't exist
	}

	// Check if source is a Conditional statement
	Conditional* condStat = dynamic_cast<Conditional*>(SrcStat);

	if (condStat != nullptr)
	{
		Point start, end, mid;

		// Determine which branch this connector belongs to
		if (condStat->getOutConnector() == this)
		{
			// Yes branch (right side)
			start = condStat->getYesOutlet();
			end = DstStat->getInlet();

			// Create an L-shaped connector
			mid.x = end.x;
			mid.y = start.y;

			// Update stored points
			Start = start;
			End = end;

			// Draw the L-shaped connector
			pOut->DrawConnector(start, mid, Output::NoDirection, Selected);
			pOut->DrawConnector(mid, end, Output::DOWN, Selected);
			pOut->DrawString(start.x + 25, start.y - 25, "YES");
		}
		else if (condStat->getNoConnector() == this)
		{
			// No branch (left side)
			start = condStat->getNoOutlet();
			end = DstStat->getInlet();

			// Create an L-shaped connector
			mid.x = end.x;
			mid.y = start.y;

			// Update stored points
			Start = start;
			End = end;

			// Draw the L-shaped connector
			pOut->DrawConnector(start, mid, Output::NoDirection, Selected);
			pOut->DrawConnector(mid, end, Output::DOWN, Selected);
			pOut->DrawString(start.x - 55, start.y - 25, "NO");
		}
	}
	else
	{
		// Normal statement (not conditional)
		Point start = SrcStat->getOutlet();
		Point end = DstStat->getInlet();

		// Make it vertical by aligning X coordinates
		end.x = start.x;

		// Update stored points (now allowed because they're mutable)
		Start = start;
		End = end;

		// Draw the connector
		pOut->DrawConnector(start, end, Output::DOWN, Selected);
	}
}

void Connector::setOutletBranch(int branch)
{
	OutletBranch = branch;
}

int Connector::getOutletBranch() const
{
	return OutletBranch;
}

void Connector::Save(std::ofstream& OutFile)
{
	int srcID = SrcStat ? SrcStat->GetID() : -1;
	int dstID = DstStat ? DstStat->GetID() : -1;

	OutFile << srcID << " " << dstID << " " << OutletBranch << std::endl;
}

void Connector::Load(ifstream& Infile, Statement** StatList, int StatCount)
{
	int srcID, dstID;
	Infile >> srcID >> dstID >> OutletBranch;

	SrcStat = nullptr;
	DstStat = nullptr;

	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->GetID() == srcID)
		{
			SrcStat = StatList[i];
		}
		if (StatList[i]->GetID() == dstID)
		{
			DstStat = StatList[i];
		}
	}
}