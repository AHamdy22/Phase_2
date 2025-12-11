#include "Read.h"
#include <fstream>

void Read::UpdateStatementText()
{
	Text = "Read " + VarName;
}

Read::Read(Point LCorner, string var)
{
	VarName = var;
	UpdateStatementText();
	LeftCorner = LCorner;
	Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READ_HI;
}

void Read::Draw(Output* pOut) const
{
	pOut->DrawRead(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

Point Read::getInlet() const
{
	return Inlet;
}

Point Read::getOutlet() const
{
	return Outlet;
}

bool Read::InStatement(Point p) const
{
	return (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.READ_WDTH &&
		p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READ_HI);
}

void Read::Save(std::ofstream& OutFile)
{
	OutFile << "READ " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << VarName << endl;
}


int Read::GetID() const
{
	return ID;
}

string Read::GetText() const
{
	return Text;
}

string Read::GetType() const
{
	return "READ";
}

void Read::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> VarName;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READ_HI;
}

void Read::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Inlet.x += x;
	Inlet.y += y;

	Outlet.x += x;
	Outlet.y += y;
}
