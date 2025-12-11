#include "End.h"
#include <sstream>

using namespace std;

End::End(Point Lcorner)
{

	LeftCorner = Lcorner;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

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
