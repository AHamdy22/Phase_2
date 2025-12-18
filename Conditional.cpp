#include "Conditional.h"
#include <sstream>
#include <fstream>

using namespace std;

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
	LeftCorner = Tcorner;  // LeftCorner here is considered the top corner point of the statement

	pOutConn = NULL;	//No connectors yet
	pNoConn = NULL;	    //No connectors yet

	Inlet.x = Tcorner.x;
	Inlet.y = Tcorner.y;

	YesOutlet.x = Tcorner.x + (UI.COND_WDTH / 2);
	YesOutlet.y = Tcorner.y + (UI.COND_HI / 2);

	NoOutlet.x = Tcorner.x - (UI.COND_WDTH / 2);
	NoOutlet.y = Tcorner.y + (UI.COND_HI / 2);

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

string Conditional::getLHS() const
{
	return LHS;
}

string Conditional::getVariableRHS() const
{
	return VariableRHS;
}


void Conditional::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawCondition(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}


//This function should be called when LHS or RHS changes
void Conditional::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << CompOperator;
	if (VariableRHS == "")
		T << ValueRHS;
	else
		T << VariableRHS;

	Text = T.str();
}
bool Conditional::InStatement(Point P) const
{
	// Assume that the conditional statement is a square; as it is difficult to determine the positions inside it if it is rhombus
	return (P.x >= LeftCorner.x - UI.COND_WDTH / 2 && P.x <= LeftCorner.x + UI.COND_WDTH / 2 + UI.ASSGN_WDTH
		&&  P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.COND_HI);
}

Point Conditional::getInlet() const
{
	return Inlet;
}

Point Conditional::getOutlet() const
{
	// There is no single outlet for Conditional statement
	Point p(-1, -1);
	return p;
}

Point Conditional::getYesOutlet() const
{
	return YesOutlet;
}

Point Conditional::getNoOutlet() const
{
	return NoOutlet;
}

void Conditional::setNoConnector(Connector* pConn)
{
	pNoConn = pConn;
}

Connector* Conditional::getNoConnector() const
{
	return pNoConn;
}

int Conditional::GetID() const
{
	return ID;
}

string Conditional::GetText() const
{
	return Text;
}

string Conditional::GetType() const
{
	return "CONDITIONAL";
}

void Conditional::Save(ofstream& OutFile)
{
	OutFile << "COND " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << CompOperator << " ";
	if (VariableRHS == "")
		OutFile << ValueRHS << " " << "0" << endl; // 0 indicates that RHS is a value
	else
		OutFile << "1" << " " << VariableRHS << endl; // 1 indicates that RHS is a variable
}


void Conditional::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;
	Inlet.x += x;
	Inlet.y += y;
	YesOutlet.x += x;
	YesOutlet.y += y;
	NoOutlet.x += x;
	NoOutlet.y += y;
}