#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point Lcorner)
{

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet


	Outlet.x = LeftCorner.x + (UI.ASSGN_WDTH / 2);
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	CountStart++;

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

Point Start::getInlet() const
{
	Point p;
	p.x = -1; // No inlet for Start statement
	p.y = -1;
	return p;
}

Point Start::getOutlet() const
{
	return Outlet;
}

int Start::GetID() const
{
	return ID;
}

string Start::GetText() const
{
	return Text;
}

string Start::GetType() const
{
	return "START";
}

void Start::Save(ofstream& OutFile)
{
	OutFile << "START " << ID << " " << LeftCorner.x << " " << LeftCorner.y << endl;
}


void Start::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Outlet.x += x;
	Outlet.y += y;
}

bool Start::Validate(ApplicationManager* pApp)
{
	Output* pOut = pApp->GetOutput();

	// There should be only one Start statement in the flowchart
	if (CountStart != 1)
	{
		pOut->PrintMessage("Error: There should be only one Start statement in the flowchart.");
		return false;
	}
	// statement without outgoing connector
	Connector* outConn = getOutConnector();
	if (outConn == NULL)
	{
		pOut->PrintMessage("Error: Start statement must have an incoming connector.");
		return false;
	}
	return true;
}


Start::~Start()
{
	CountStart--;
}
int Start::CountStart = 0;