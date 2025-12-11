#include "Connector.h"
#include<fstream>
#include"Statements\Statement.h"


Connector::Connector(Statement* Src, Statement* Dst)
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
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

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::SetSelected(bool s)
{
	Selected = s;
}



void Connector::Draw(Output* pOut) const
{
	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
	if (SrcStat == nullptr || DstStat == nullptr)
	{
		return;  // Don't draw if statements don't exist
	}

	Point start = SrcStat->getOutlet();
	Point end = DstStat->getInlet();

	// Make it vertical by aligning X coordinates
	end.x = start.x;

	// Update stored points
	const_cast<Connector*>(this)->Start = start;
	const_cast<Connector*>(this)->End = end;

	// Draw the connector
	pOut->DrawConnector(start, end, Output::DOWN, Selected);
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
	// Save the IDs of the source and destination statements
	// If a statement is null, save -1
	int srcID = SrcStat ? SrcStat->GetID() : -1;
	int dstID = DstStat ? DstStat->GetID() : -1;

	// If OutletBranch is an int, use it directly. If it's a string, output the string.
	OutFile << srcID << " " << dstID << " " << OutletBranch << std::endl;
}

void Connector::Load(ifstream& Infile, Statement** StatList, int StatCount)
{
	int srcID, dstID;
	Infile >> srcID >> dstID >> OutletBranch;
	// Find the source statement by ID
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