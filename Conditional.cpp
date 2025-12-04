#include "Conditional.h"
#include <sstream>

using namespace std;
//window w;
//window *pW = &w;
Conditional::Conditional(Point Tcorner, string LeftHS, double ValueRightHS, string VariableRightHS, string Operator)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	ValueRHS = ValueRightHS;
	VariableRHS = VariableRightHS;
	CompOperator = Operator;

	UpdateStatementText();

	//pW->GetStringSize(stringlength, stringheight, Text);
	TopCorner = Tcorner;

	pOutConn1 = NULL;	//No connectors yet
	pOutConn2 = NULL;	//No connectors yet

	Inlet.x = Tcorner.x;
	Inlet.y = Tcorner.y;

	Outlet1.x = Tcorner.x - (UI.ASSGN_WDTH/2);
	Outlet1.y = Tcorner.y + (UI.ASSGN_HI/2);

	Outlet2.x = Tcorner.x + (UI.ASSGN_WDTH / 2);
	Outlet2.y = Tcorner.y + (UI.ASSGN_HI / 2);

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


void Conditional::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawCondition(TopCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}


//This function should be called when LHS or RHS changes
void Conditional::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << CompOperator ;
	if (VariableRHS == "")
		T << ValueRHS;
	else
		T << VariableRHS;

	Text = T.str();
}
