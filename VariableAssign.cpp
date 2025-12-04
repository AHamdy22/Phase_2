#include "VariableAssign.h"
#include <sstream>


using namespace std;
//window w;
//window *pW = &w;
VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	
	LHS = LeftHS;
	RHS = RightHS;

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

void VariableAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}

void VariableAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}



void VariableAssign::UpdateStatementText()
{
	
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}