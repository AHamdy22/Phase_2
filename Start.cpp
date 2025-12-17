#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point Lcorner)
{

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet


	Outlet.x = LeftCorner.x + (UI.ASSGN_WDTH / 2);
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}

void Start::Draw(Output* pOut) const
{
		
	pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "Start", Selected);

}

Point Start::GetPosition() const
{
	return LeftCorner;
}

void Start::SetPosition(Point p)
{
	LeftCorner = p;
}

void Start::EditStatement(ApplicationManager* pApp, Point p)
{

	AddStart* D = new AddStart(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	delete D;
}

void Start::GetStatementCut(ApplicationManager* pApp) const
{
	Start* S = new Start(*this);
	S->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(S);

}


void Start::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Start* s = dynamic_cast<Start*>(S);
	if (s)
	{
		if (s->IsCopied())
		{
			s->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			s = new Start(*s);
			p.x -= UI.ASSGN_WDTH / 2;
			s->SetPosition(p);
			s->SetSelected(false);
			pManager->AddStatement(s);
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 2;
			s->SetPosition(p);
			s->SetSelected(false);
			pManager->AddStatement(s);
			//pManager->SetClipboard(nullptr);
		}
	}

}

void Start::UpdateStatementText()
{
}

bool Start::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.START_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.START_HI);
}