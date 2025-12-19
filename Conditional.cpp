#include "Conditional.h"
#include "AddConditional.h"
#include <sstream>
#include <fstream>

using namespace std;

Conditional::Conditional(Point Tcorner, string LeftHS, double ValueRightHS, string VariableRightHS, string Operator)
{
	LHS = LeftHS;
	ValueRHS = ValueRightHS;
	VariableRHS = VariableRightHS;
	CompOperator = Operator;

	UpdateStatementText();

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
	return (P.x >= LeftCorner.x - UI.COND_WDTH / 2 && P.x <= LeftCorner.x + UI.COND_WDTH / 2
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

bool Conditional::validate(ApplicationManager* pApp) const
{
	Output* pOut = pApp->GetOutput();

	// LHS variable not declared
	if (!(pApp->IsVariableDeclared(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		return false;
	}

	// LHS variable is initialized
	if (!(pApp->IsVariableInitialized(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not initialized.");
		pApp->SetVariableInitialized(LHS, false);
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

	// RHS is a value (not a variable)
	if (VariableRHS == "")
	{
		return true;
	}

	// RHS variable not declared
	if (!(pApp->IsVariableDeclared(VariableRHS)))
	{
		pOut->PrintMessage("Error: Variable '" + VariableRHS + "' is not declared.");
		return false;
	}

	// RHS variable is initialized
	if (!(pApp->IsVariableInitialized(VariableRHS)))
	{
		pOut->PrintMessage("Error: Variable '" + VariableRHS + "' is not initialized.");
		pApp->SetVariableInitialized(VariableRHS, false);
		return false;
	}
	pApp->SetVariableInitialized(LHS, true);
	pApp->SetVariableInitialized(VariableRHS, true);
	return true;
}

void Conditional::Simulate(ApplicationManager* pApp)
{
	double lhsValue = pApp->GetVariableValue(LHS);
	double rhsValue = (VariableRHS == "") ? ValueRHS : pApp->GetVariableValue(VariableRHS);

	bool cond = false;

	if (CompOperator == ">")
		cond = (lhsValue > rhsValue);
	else if (CompOperator == "<")
		cond = (lhsValue < rhsValue);
	else if (CompOperator == ">=")
		cond = (lhsValue >= rhsValue);
	else if (CompOperator == "<=")
		cond = (lhsValue <= rhsValue);
	else if (CompOperator == "==")
		cond = (lhsValue == rhsValue);
	else if (CompOperator == "!=")
		cond = (lhsValue != rhsValue);

	Connector* nextConn = cond ? getOutConnector() : getNoConnector();

	pApp->SetNextStatement(nextConn->getDstStat());
}

void Conditional::GetStatementCut(ApplicationManager* pApp) const
{
	Conditional* C = new Conditional(*this);
	C->SetSelected(false);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(C);

}

Point Conditional::GetPosition() const
{
	return LeftCorner;
}

void Conditional::SetPosition(Point p)
{
	LeftCorner = p;
}

void Conditional::PasteStatement(Statement* S, Point p, Output* pOut, ApplicationManager* pManager) const
{

	Conditional* c = dynamic_cast<Conditional*>(S);
	if (c)
	{
		if (c->IsCopied())
		{
			c->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			c = new Conditional(*c);
			c->SetPosition(p);
			c->SetSelected(false);
			pManager->AddStatement(c);
		}
		else
		{
			c->SetPosition(p);
			c->SetSelected(false);
			pManager->AddStatement(c);
		}
	}
}

void Conditional::EditStatement(ApplicationManager* pApp, Point p)
{

	AddConditional* D = new AddConditional(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	LHS = D->GetLHS();

	ValueRHS = D->GetValueRHS();

	VariableRHS = D->GetVariableRHS();

	CompOperator = D->GetCompOperator();

	UpdateStatementText();

	delete D;
}