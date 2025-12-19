#include "Write.h"
#include <fstream>
#include "AddWrite.h"
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
		pApp->SetVariableInitialized(VarName, false);
		return false; // Variable not declared
	}

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a Write statement without an outgoing connector.");
		return false; // No outgoing connector
	}
	pApp->SetVariableInitialized(VarName, true);
	return true; // Valid
}

Point Write::GetPosition() const
{
	return LeftCorner;
}

void Write::SetPosition(Point p)
{
	LeftCorner = p;
}

void Write::EditStatement(ApplicationManager* pApp, Point p)
{

	AddWrite* D = new AddWrite(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	VarName = D->GetVarName();

	UpdateStatementText();

	delete D;
}

void Write::GetStatementCut(ApplicationManager* pApp) const
{
	Write* W = new Write(*this);
	W->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(W);

}

void Write::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Write* w = dynamic_cast<Write*>(S);
	if (w)
	{
		if (w->IsCopied())
		{
			w->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			w = new Write(*w);
			p.x -= UI.ASSGN_WDTH / 3;
			w->SetPosition(p);
			w->SetSelected(false);
			pManager->AddStatement(w);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 3;
			w->SetPosition(p);
			w->SetSelected(false);
			pManager->AddStatement(w);
		}
	}
}

void Write::Simulate(ApplicationManager* pApp)
{
	Output* pOut = pApp->GetOutput();
	double value = pApp->GetVariableValue(VarName);
	pOut->PrintOutput(to_string(value) + " ");
}