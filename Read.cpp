#include "Read.h"
#include <fstream>

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

Point Read::GetPosition() const
{
	return LeftCorner;
}

void Read::SetPosition(Point p)
{
	LeftCorner = p;
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
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 3;
			r->SetPosition(p);
			r->SetSelected(false);
			pManager->AddStatement(r);
			//pManager->SetClipboard(nullptr);
		}
	}

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

void Read::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> VarName;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READ_HI;
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