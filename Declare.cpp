
#include "Declare.h"
#include <sstream>
#include <fstream>

using namespace std;

Declare::Declare(Point Lcorner, string data_type, string variable)
{
	DataType = data_type;
	Var = variable;

	UpdateStatementText();

	// REMOVED: stringlength, stringheight, and GetStringSize call
	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Declare::setDataType(const string& d)
{
	DataType = d;
	UpdateStatementText();
}

void Declare::setVar(const string& v)
{
	Var = v;
	UpdateStatementText();
}

bool Declare::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI);
}

Point Declare::GetPosition() const
{
	return LeftCorner;
}

void Declare::SetPosition(Point p)
{
	LeftCorner = p;
}

void Declare::Draw(Output* pOut) const
{
	pOut->DrawDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void Declare::UpdateStatementText()
{
	ostringstream T;
	T << DataType << " " << Var;
	Text = T.str();
}

Point Declare::getInlet() const
{
	return Inlet;
}

Point Declare::getOutlet() const
{
	return Outlet;
}

int Declare::GetID() const
{
	return ID;
}

string Declare::GetText() const
{
	return Text;
}

string Declare::GetType() const
{
	return "DECLARE";
}

void Declare::Save(ofstream& OutFile)
{
	OutFile << "DECLARE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << DataType << " " << Var << endl;
}

void Declare::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> DataType >> Var;
	UpdateStatementText();

	// Recalculate inlet and outlet positions
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Declare::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;
	Inlet.x += x;
	Inlet.y += y;
	Outlet.x += x;
	Outlet.y += y;
}

bool Declare::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();
	if (pApp->IsVariableDeclared(Var))
	{
		pOut->PrintMessage("Error: Variable '" + Var + "' is already declared.");
		return false;
	}

	// Check if has output connector (except for End statement)
	if (!pOutConn)
	{
		pOut->PrintMessage("Error: There is a statement without an output connector.");
		return false;
	}

	// Declare the variable
	pApp->DeclareVariable(Var);

	return true;
}
