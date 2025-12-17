#include "Write.h"

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

void Write::Draw(Output* pOut) const
{
	pOut->DrawWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

bool Write::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x - (UI.READ_WDTH / 4) && P.x <= LeftCorner.x + UI.READ_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.READ_HI);
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
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 3;
			w->SetPosition(p);
			w->SetSelected(false);
			pManager->AddStatement(w);
			//pManager->SetClipboard(nullptr);
		}
	}

}