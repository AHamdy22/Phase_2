#include "VariableAssign.h"
#include <sstream>


using namespace std;
//window w;
//window *pW = &w;
VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	
	LHS = LeftHS;
	RHS = RightHS;

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

void VariableAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}

bool VariableAssign::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI);
}

Point VariableAssign::GetPosition() const
{
	return LeftCorner;
}

void VariableAssign::SetPosition(Point p)
{
	LeftCorner = p;
}

void VariableAssign::EditStatement(ApplicationManager* pApp, Point p)
{

	AddVariableAssign* D = new AddVariableAssign(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	LHS = D->GetLHS();

	RHS = D->GetRHS();

	UpdateStatementText();

	delete D;
}
void VariableAssign::GetStatementCut(ApplicationManager* pApp) const
{
	VariableAssign* V = new VariableAssign(*this);
	V->SetSelected(false);
	V->addInConnector(nullptr);
	V->setOutConnector(nullptr);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(V);

}


void VariableAssign::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	VariableAssign* v = dynamic_cast<VariableAssign*>(S);
	if (v)
	{
		if (v->IsCopied())
		{
			v->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			v = new VariableAssign(*v);
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

void VariableAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


int VariableAssign::GetID() const
{
	return ID;
}

string VariableAssign::GetText() const
{
	return Text;
}

string VariableAssign::GetType() const
{
	return "VARIABLE ASSIGNMENT";
}

void VariableAssign::Save(ofstream& OutFile)
{
	OutFile << "VARIABLE_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}

void VariableAssign::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;
	Inlet.x += x;
	Inlet.y += y;
	Outlet.x += x;
	Outlet.y += y;
}

Point VariableAssign::getInlet() const
{
	return Inlet;
}

Point VariableAssign::getOutlet() const
{
	return Outlet;
}


bool VariableAssign::Validate(ApplicationManager* pApp)
{
	Output* pOut = pApp->GetOutput();
	if (!(pApp->IsVariableDeclared(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		return false;
	}

	if (!(pApp->IsVariableDeclared(RHS)))
	{
		pOut->PrintMessage("Error: Variable '" + RHS + "' is not declared.");
		return false;
	}

	if (!(pApp->IsVariableInitialized(RHS)))
	{
		pOut->PrintMessage("Error: Variable '" + RHS + "' is not initialized.");
		return false;
	}

	// Check if there is an incoming connector
	Connector* inConn = getInConnector(0);
	if (inConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a \"Variable Assign\" statement without an incoming connector.");
		return false; // No incoming connector
	}

	// Check if there is an outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == nullptr)
	{
		pOut->PrintMessage("Error: There is a \"Variable Assign\" statement without an outgoing connector.");
		return false; // No outgoing connector
	}

	pApp->SetVariableValue(LHS, pApp->GetVariableValue(RHS));
	return true;
}

void VariableAssign::Simulate(ApplicationManager* pManager)
{

}





void VariableAssign::UpdateStatementText()
{
	
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}