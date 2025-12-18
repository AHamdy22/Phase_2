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

string Read::getVar() const
{
	return VarName;
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

void Read::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Inlet.x += x;
	Inlet.y += y;

	Outlet.x += x;
	Outlet.y += y;
}

bool Read::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();
	// Check if the variable is declared
	if (!pApp->IsVariableDeclared(VarName))
	{
		pOut->PrintMessage("Error: Variable '" + VarName + "' used in Read statement is not declared.");
		return false; // Variable not declared
	}

	// Check if there is an incoming connector
	Connector* inConn = getInConnector(0);
	if (inConn == nullptr)
	{
		pOut->PrintMessage("Error: Thre is a Read statement without an incoming connector.");
		return false; // No incoming connector
	}

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a Read statement without an outgoing connector.");
		return false; // No outgoing connector
	}
	return true; // Valid
}
