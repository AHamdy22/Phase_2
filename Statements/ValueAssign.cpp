#include "ValueAssign.h"
#include <sstream>


using namespace std;
//window w;
//window *pW = &w;
ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	stringlength = 0;
	stringheight = 0;
	//pW->GetStringSize(stringlength, stringheight, Text);
	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

bool ValueAssign::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI);
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
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

bool ValueAssign::Validate(ApplicationManager* pApp)
{
	 Output* pOut = pApp->GetOutput();

	 if (!(pApp->IsVariableDeclared(LHS)))
	 {
		 pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		 return false;
	 }

	 if(!pOutConn)
	 {
		 pOut->PrintMessage("Error: There is a statement without an output connector.");
		 return false;
	 }

	 return true;
}

Point ValueAssign::GetPosition() const
{
	return LeftCorner;
}

void ValueAssign::SetPosition(Point p)
{
	LeftCorner = p;
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

//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

Point ValueAssign::getInlet() const
{
	return Inlet;
}

Point ValueAssign::getOutlet() const
{
	return Outlet;
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
	OutFile << "VALUE ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
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