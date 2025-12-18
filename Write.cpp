#include "Write.h"
#include<fstream>

void Write::UpdateStatementText()
{
	Text = "Write " + VarName;
}

Write::Write(Point LCorner, string var)
{
	VarName = var;
	UpdateStatementText();
	LeftCorner = LCorner;
	Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READ_HI;
}

string Write::getVar() const
{
	return VarName;
}

void Write::Draw(Output* pOut) const
{
	pOut->DrawWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

Point Write::getInlet() const
{
	return Inlet;
}

Point Write::getOutlet() const
{
	return Outlet;
}

bool Write::InStatement(Point p) const
{
	return (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.READ_WDTH &&
			p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READ_HI);
}

void Write::Save(std::ofstream& OutFile)
{
	// Changed "Write" to "WRITE" to match the Load function and other statements
	OutFile << "WRITE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << VarName << endl;
}


int Write::GetID() const
{
	return ID;
}

string Write::GetText() const
{
	return Text;
}

string Write::GetType() const
{
	return "WRITE";
}


void Write::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Inlet.x += x;
	Inlet.y += y;

	Outlet.x += x;
	Outlet.y += y;
}

bool Write::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();
	// Check if the variable is declared
	if (!pApp->IsVariableDeclared(VarName))
	{
		pOut->PrintMessage("Error: Variable '" + VarName + "' used in Write statement is not declared.");
		return false; // Variable not declared
	}

	// Check if the variable is initialized
	if (!pApp->IsVariableInitialized(VarName))
	{
		pOut->PrintMessage("Error: Variable '" + VarName + "' used in Write statement is not initialized.");
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
