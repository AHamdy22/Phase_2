#include "ValueAssign.h"
#include <sstream>
#include "..\Actions\AddValueAssign.h"

using namespace std;
ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();


	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

void ValueAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

string ValueAssign::getLHS() const
{
	return LHS;
}

double ValueAssign::getRHS() const
{
	return RHS;
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point ValueAssign::getInlet() const
{
	return Inlet;
}

Point ValueAssign::getOutlet() const
{
	return Outlet;
}

bool ValueAssign::InStatement(Point p) const
{
	return (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
			p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.ASSGN_HI);
}

int ValueAssign::GetID() const
{
	return ID;
}

string ValueAssign::GetText() const
{
	return Text;
}

string ValueAssign::GetType() const
{
	return "VALUE ASSIGNMENT";
}

void ValueAssign::Save(std::ofstream& OutFile)
{
	OutFile << "VALUE_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}


void ValueAssign::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Inlet.x += x;
	Inlet.y += y;

	Outlet.x += x;
	Outlet.y += y;
}

bool ValueAssign::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();

	if (!(pApp->IsVariableDeclared(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		return false;
	}

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a \"Value Assign\" statement without an outgoing connector.");
		return false; // No outgoing connector
	}

	pApp->SetVariableValue(LHS, RHS);

	return true;
}

void ValueAssign::Simulate(ApplicationManager* pApp)
{
	// Already done in the validation
}

Point ValueAssign::GetPosition() const
{
	return LeftCorner;
}

void ValueAssign::SetPosition(Point p)
{
	LeftCorner = p;
}

void ValueAssign::GetStatementCut(ApplicationManager* pApp) const
{
	ValueAssign* V = new ValueAssign(*this);
	V->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(V);

}


void ValueAssign::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	ValueAssign* v = dynamic_cast<ValueAssign*>(S);
	if (v)
	{
		if (v->IsCopied())
		{
			v->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			v = new ValueAssign(*v);
			p.x -= UI.ASSGN_WDTH / 2;
			v->SetPosition(p);
			v->SetSelected(false);
			pManager->AddStatement(v);
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 2;
			v->SetPosition(p);
			v->SetSelected(false);
			pManager->AddStatement(v);
			//pManager->SetClipboard(nullptr);
		}
	}
}

void ValueAssign::EditStatement(ApplicationManager* pApp, Point p)
{

	AddValueAssign* D = new AddValueAssign(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	LHS = D->GetLHS();

	RHS = D->GetRHS();

	UpdateStatementText();

	delete D;
}