#include "Start.h"

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
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "Start", Selected);

}
void Start::UpdateStatementText()
{
}

bool Start::InStatement(Point P) const
{
	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.START_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.START_HI);
}