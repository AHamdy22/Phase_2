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
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "Start", Selected);

}

void Start::UpdateStatementText()
{
}
