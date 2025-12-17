#include "Conditional.h"
#include <sstream>

using namespace std;
//window w;
//window *pW = &w;
Conditional::Conditional(Point T, string LeftHS, double ValueRightHS, string VariableRightHS, string Operator)
{
	
	LHS = LeftHS;
	ValueRHS = ValueRightHS;
	VariableRHS = VariableRightHS;
	CompOperator = Operator;

	UpdateStatementText();


	Top = T;

	pOutConn1 = NULL;	
	pOutConn2 = NULL;	

	Inlet.x = T.x;
	Inlet.y = T.y;

	Outlet1.x = T.x - (UI.ASSGN_WDTH / 2);
	Outlet1.y = T.y + (UI.ASSGN_HI / 2);

	Outlet2.x = T.x + (UI.ASSGN_WDTH / 2);
	Outlet2.y = T.y + (UI.ASSGN_HI / 2);

}

void Conditional::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void Conditional::setValueRHS(double ValueR)
{
	ValueRHS = ValueR;
	UpdateStatementText();
}

void Conditional::setVariableRHS(string VariableR)
{
	VariableRHS = VariableR;
	UpdateStatementText();
}

void Conditional::setCompOperator(string Operator)
{
	CompOperator = Operator;
	UpdateStatementText();
}

Point Conditional::GetPosition() const
{
	return Top;
}

void Conditional::SetPosition(Point p)
{
	Top = p;
}

void Conditional::EditStatement(ApplicationManager* pApp, Point p)
{

	AddConditional* D = new AddConditional(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	LHS = D->GetLHS();

	ValueRHS = D->GetValueRHS();

	VariableRHS = D->GetVariableRHS();

	CompOperator = D->GetCompOperator();

	UpdateStatementText();

	delete D;
}

void Conditional::GetStatementCut(ApplicationManager* pApp) const
{
	Conditional* C = new Conditional(*this);
	C->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(C);

}


void Conditional::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Conditional* c = dynamic_cast<Conditional*>(S);
	if (c)
	{
		if (c->IsCopied())
		{
			c->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			c = new Conditional(*c);
			c->SetPosition(p);
			c->SetSelected(false);
			pManager->AddStatement(c);
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			c->SetPosition(p);
			c->SetSelected(false);
			pManager->AddStatement(c);
			//pManager->SetClipboard(nullptr);
		}
	}

}

void Conditional::Draw(Output* pOut) const
{
	 	
	pOut->DrawCondition(Top, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}



void Conditional::UpdateStatementText()
{
	
	ostringstream T;
	T << LHS << CompOperator;
	if (VariableRHS == "")
		T << ValueRHS;
	else
		T << VariableRHS;

	Text = T.str();
}

bool Conditional::InStatement(Point P) const
{
	return (P.x >= Top.x - (UI.ASSGN_WDTH / 2) && P.x <= Top.x + (UI.ASSGN_WDTH / 2) &&
		P.y >= Top.y && P.y <= Top.y + UI.ASSGN_HI );
}