#include "OperatorAssign.h"
#include <sstream>


using namespace std;
//window w;
//window *pW = &w;
OperatorAssign::OperatorAssign(Point Lcorner, string LeftHS , double valop1 , string varop1 , double valop2 , string varop2 , char arthop)
{

	LHS = LeftHS;
	valOP1 = valop1;
	varOP1 = varop1;
	valOP2 = valop2;
	varOP2 = varop2;
	Operation = arthop;

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

void OperatorAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void OperatorAssign::setvarOP1(const string& o1)
{
	varOP1 = o1;
	UpdateStatementText();
}

void OperatorAssign::setvalOP1(double p1)
{
	valOP1 = p1;
	UpdateStatementText();
}

void OperatorAssign::setvalOP2(double p2)
{
	valOP2 = p2;
	UpdateStatementText();
}

bool OperatorAssign::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI);
}

void OperatorAssign::setvarOP2(const string& o2)
{
	varOP2 = o2;
	UpdateStatementText();
}

Point OperatorAssign::GetPosition() const
{
	return LeftCorner;
}

void OperatorAssign::SetPosition(Point p)
{
	LeftCorner = p;
}

void OperatorAssign::EditStatement(ApplicationManager* pApp, Point p)
{

	AddOperatorAssign* D = new AddOperatorAssign(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	LHS = D->GetLHS();

	varOP1 = D->GetvarOP1();

	valOP1 = D->GetvalOP1();

	varOP2 = D->GetvarOP2();

	valOP2 = D->GetvalOP2();

	UpdateStatementText();

	delete D;
}

void OperatorAssign::GetStatementCut(ApplicationManager* pApp) const
{
	OperatorAssign* O = new OperatorAssign(*this);
	O->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(O);

}


void OperatorAssign::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	OperatorAssign* o = dynamic_cast<OperatorAssign*>(S);
	if (o)
	{
		if (o->IsCopied())
		{
			o->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			o = new OperatorAssign(*o);
			p.x -= UI.ASSGN_WDTH / 2;
			o->SetPosition(p);
			o->SetSelected(false);
			pManager->AddStatement(o);
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 2;
			o->SetPosition(p);
			o->SetSelected(false);
			pManager->AddStatement(o);
			//pManager->SetClipboard(nullptr);
		}
	}

}

void OperatorAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}



void OperatorAssign::UpdateStatementText()
{

	ostringstream T;
	T << LHS << " = ";
	if (varOP1 == "")
		T << valOP1;
	else
		T << varOP1;

	T <<" "<< Operation<<" ";

	if (varOP2 == "")
		T << valOP2;
	else
		T << varOP2;

	Text = T.str();
}