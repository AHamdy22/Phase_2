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

