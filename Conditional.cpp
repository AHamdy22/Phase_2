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
	TopCorner = Tcorner;

	pOutConn = NULL;	//No connectors yet
	pNoConn = NULL;	    //No connectors yet

	Inlet.x = Tcorner.x;
	Inlet.y = Tcorner.y;

	YesOutlet.x = Tcorner.x + (UI.ASSGN_WDTH / 2);
	YesOutlet.y = Tcorner.y + (UI.ASSGN_HI / 2);

	NoOutlet.x = Tcorner.x - (UI.ASSGN_WDTH / 2);
	NoOutlet.y = Tcorner.y + (UI.ASSGN_HI / 2);

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
	return (P.x >= TopCorner.x - UI.ASSGN_WDTH / 2 && P.x <= TopCorner.x + UI.ASSGN_WDTH / 2 + UI.ASSGN_WDTH
		&&  P.y >= TopCorner.y && P.y <= TopCorner.y + UI.ASSGN_HI);
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
	OutFile << "COND " << ID << " " << TopCorner.x << " " << TopCorner.y << " " << LHS << " " << CompOperator << " ";
	if (VariableRHS == "")
		OutFile << ValueRHS << " " << "0" << endl; // 0 indicates that RHS is a value
	else
		OutFile << "0" << " " << VariableRHS << endl; // 0 indicates that RHS is a variable
}

void Conditional::Load(ifstream& Infile)
{
	string varRHS;
	double valRHS;

	// Read ID first, then other parameters
	Infile >> ID >> TopCorner.x >> TopCorner.y >> LHS >> CompOperator >> valRHS >> varRHS;

	if (varRHS == "0")
	{
		ValueRHS = valRHS;
		VariableRHS = "";
	}
	else
	{
		ValueRHS = 0;
		VariableRHS = varRHS;
	}

	UpdateStatementText();

	// Recalculate inlet and outlet positions
	Inlet.x = TopCorner.x;
	Inlet.y = TopCorner.y;

	YesOutlet.x = TopCorner.x + (UI.ASSGN_WDTH / 2);
	YesOutlet.y = TopCorner.y + (UI.ASSGN_HI / 2);

	NoOutlet.x = TopCorner.x - (UI.ASSGN_WDTH / 2);
	NoOutlet.y = TopCorner.y + (UI.ASSGN_HI / 2);
}

void Conditional::Move(int x, int y)
{
	TopCorner.x += x;
	TopCorner.y += y;
	Inlet.x += x;
	Inlet.y += y;
	YesOutlet.x += x;
	YesOutlet.y += y;
	NoOutlet.x += x;
	NoOutlet.y += y;
}

bool Conditional::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();

	// LHS variable not declared
	if (!(pApp->IsVariableDeclared(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		return false;
	}

	// RHS variable not declared
	if (!(pApp->IsVariableDeclared(VariableRHS)))
	{
		pOut->PrintMessage("Error: Variable '" + VariableRHS + "' is not declared.");
		return false;
	}

	// statement without outgoing connectors
	Connector* yesConn = getOutConnector();
	Connector* noConn = getNoConnector();
	if (yesConn == NULL || noConn == NULL)
	{
		pOut->PrintMessage("Error: Conditional statement must have two outgoing connectors (Yes and No).");
		return false;
	}

	return true;

}