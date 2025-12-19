#include "Read.h"
#include <fstream>
#include "AddRead.h"

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
		pApp->SetVariableInitialized(VarName, false);
		return false; // Variable not declared
	}

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a Read statement without an outgoing connector.");
		pApp->SetVariableInitialized(VarName, false);
		return false; // No outgoing connector
	}
	pApp->SetVariableInitialized(VarName, true);
	return true; // Valid
}

void Read::Simulate(ApplicationManager* pApp)
{
	Output* pOut = pApp->GetOutput();
	Input* pIn = pApp->GetInput();
	pOut->PrintMessage("Enter value for '" + VarName + "':");
	double val = pIn->GetValue(pOut);
	pApp->SetVariableValue(VarName, val);
}

Point Read::GetPosition() const
{
	return LeftCorner;
}

void Read::SetPosition(Point p)
{
	LeftCorner = p;
}

void Read::GetStatementCut(ApplicationManager* pApp) const
{
	Read* R = new Read(*this);
	R->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(R);

}


void Read::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Read* r = dynamic_cast<Read*>(S);
	if (r)
	{
		if (r->IsCopied())
		{
			r->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			r = new Read(*r);
			p.x -= UI.ASSGN_WDTH / 3;
			r->SetPosition(p);
			r->SetSelected(false);
			pManager->AddStatement(r);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 3;
			r->SetPosition(p);
			r->SetSelected(false);
			pManager->AddStatement(r);
		}
	}
}


void Read::EditStatement(ApplicationManager* pApp, Point p)
{

	AddRead* D = new AddRead(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	VarName = D->GetVarName();

	UpdateStatementText();

	delete D;
}
