#include "Declare.h"
#include <sstream>
#include <fstream>
#include "AddDeclare.h"

using namespace std;

Declare::Declare(Point Lcorner, string data_type, string variable)
{
	DataType = data_type;
	Var = variable;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;

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

string Declare::getVar() const
{
	return Var;
}

bool Declare::InStatement(Point p) const
{
	return (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.ASSGN_HI);
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

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a \"Declare\" statement without an outgoing connector.");
		return false; // No outgoing connector
	}

	// Declare the variable
	pApp->DeclareVariable(Var);

	return true;
}

void Declare::Simulate(ApplicationManager* pApp)
{
	// Already done in the validation
}

void Declare::GetStatementCut(ApplicationManager* pApp) const
{
	Declare* D = new Declare(*this);
	D->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(D);
}


void Declare::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Declare* d = dynamic_cast<Declare*>(S);
	if (d)
	{
		if (d->IsCopied())
		{
			d->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			d = new Declare(*d);
			p.x -= UI.ASSGN_WDTH / 2;
			d->SetPosition(p);
			d->SetSelected(false);
			pManager->AddStatement(d);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 2;
			d->SetPosition(p);
			d->SetSelected(false);
			pManager->AddStatement(d);
		}
	}
}

void Declare::EditStatement(ApplicationManager* pApp, Point p)
{

	AddDeclare* D = new AddDeclare(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	Var = D->GetVar();

	UpdateStatementText();

	delete D;
}