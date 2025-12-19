#include "End.h"
#include <sstream>

using namespace std;

End::End(Point Lcorner)
{

	LeftCorner = Lcorner;

	Inlet.x = LeftCorner.x + UI.START_WDTH / 2;
	Inlet.y = LeftCorner.y;

	CountEnd++;

}

Point End::GetPosition() const
{
	return LeftCorner;
}

void End::SetPosition(Point p)
{
	LeftCorner = p;
}


void End::EditStatement(ApplicationManager* pApp, Point p)
{

	AddEnd* D = new AddEnd(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	delete D;
}

void End::GetStatementCut(ApplicationManager* pApp) const
{
	End* E = new End(*this);
	E->SetSelected(false);
	E->addInConnector(nullptr);
	E->setOutConnector(nullptr);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(E);

}


void End::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	End* e = dynamic_cast<End*>(S);
	if (e)
	{
		if (e->IsCopied())
		{
			e->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			e = new End(*e);
			p.x -= UI.ASSGN_WDTH / 2;
			e->SetPosition(p);
			e->SetSelected(false);
			pManager->AddStatement(e);
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			p.x -= UI.ASSGN_WDTH / 2;
			e->SetPosition(p);
			e->SetSelected(false);
			pManager->AddStatement(e);
			//pManager->SetClipboard(nullptr);
		}
	}

}

void End::Draw(Output* pOut) const
{
 	
	pOut->DrawEnd(LeftCorner, UI.START_WDTH, UI.START_HI, "End", Selected);

}

void End::UpdateStatementText()
{
}

bool End::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.START_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.START_HI);
}

Point End::getInlet() const
{
	return Inlet;
}

Point End::getOutlet() const
{
	Point p;
	p.x = -1; // No outlet for End statement
	p.y = -1;
	return p;
}

int End::GetID() const
{
	return ID;
}

string End::GetText() const
{
	return Text;
}

string End::GetType() const
{
	return "END";
}

void End::Save(ofstream& OutFile)
{
	OutFile << "END " << ID << " " << LeftCorner.x << " " << LeftCorner.y << endl;
}


void End::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Inlet.x += x;
	Inlet.y += y;
}

bool End::Validate(ApplicationManager* pApp)
{
	Output* pOut = pApp->GetOutput();

	// There should be only one Start statement in the flowchart
	if (CountEnd != 1)
	{
		//pOut->PrintMessage("Error: There should be only one End statement in the flowchart.");
		//return false;
	}
	// statement without incoming connector
	Connector* inConn = getInConnector(0);
	if (inConn == NULL)
	{
		pOut->PrintMessage("Error: End statement must have an incoming connector.");
		return false;
	}
	return true;
}

void End::Simulate(ApplicationManager* pApp)
{

}

End::~End()
{
	CountEnd--;
}

int End::CountEnd = 0; //Initialize static data member