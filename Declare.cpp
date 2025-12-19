#include "Declare.h"
#include <sstream>


using namespace std;
//window w;
//window *pW = &w;
Declare::Declare(Point Lcorner, string variable)
{
	
	Var = variable;

	UpdateStatementText();

	stringlength = 0;
	stringheight = 0;
	//pW->GetStringSize(stringlength, stringheight, Text);
	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
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

void Declare::EditStatement(ApplicationManager* pApp, Point p)
{

	AddDeclare* D = new AddDeclare(pApp);
	
	D->SetPosition(p);

	D->ReadActionParameters();

	Var = D->GetVar();

	UpdateStatementText();

	delete D;
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
		if(d->IsCopied())
		{
			d->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			d = new Declare(*d);
			p.x -= UI.ASSGN_WDTH / 2;
			d->SetPosition(p);
			d->SetSelected(false);
			pManager->AddStatement(d);
			//pManager->SetClipboard(nullptr);
		}
		else
			{
			p.x -= UI.ASSGN_WDTH / 2;
			d->SetPosition(p);
			d->SetSelected(false);
			pManager->AddStatement(d);
			//pManager->SetClipboard(nullptr);
			}
	}
	
}

void Declare::Draw(Output* pOut) const
{
		
	pOut->DrawDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool Declare::Validate(ApplicationManager* pApp) 
{
	 Output* pOut = pApp->GetOutput();

	if (pApp->IsVariableDeclared(Var))
	{
		pOut->PrintMessage("Error: Variable '" + Var + "' is already declared.");
		return false;
	}

	// Check if there is an incoming connector
	Connector* inConn = getInConnector(0);
	if (inConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a \"Declare\" statement without an incoming connector.");
		return false; // No incoming connector
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

void Declare::UpdateStatementText()
{
	
	ostringstream T;
	T << "Declare" << " " << Var;
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
	OutFile << "DECLARE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << Var << endl;
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