#include "Conditional.h"
#include <sstream>
#include <fstream>

using namespace std;
//window w;
//window *pW = &w;
Conditional::Conditional(Point T, string LeftHS, double ValueRightHS, string VariableRightHS, string Operator)
{
	
	LHS = LeftHS;
	ValueRHS = ValueRightHS;
	VariableRHS = VariableRightHS;
	CompOperator = Operator;

	UpdateStatementText();


	Top = T;

	pOutConn = NULL;	
	pNoConn = NULL;	

	Inlet.x = T.x;
	Inlet.y = T.y;

	YesOutlet.x = Top.x + (UI.ASSGN_WDTH / 2);
	YesOutlet.y = Top.y + (UI.ASSGN_HI / 2);

	NoOutlet.x = Top.x - (UI.ASSGN_WDTH / 2);
	NoOutlet.y = Top.y + (UI.ASSGN_HI / 2);


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

Point Conditional::GetPosition() const
{
	return Top;
}

void Conditional::SetPosition(Point p)
{
	Top = p;
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

void Conditional::GetStatementCut(ApplicationManager* pApp) const
{
	Conditional* C = new Conditional(*this);
	C->SetSelected(false);
	C->addInConnector(nullptr);
	C->setOutConnector(nullptr);
	pApp->DeleteStatement(pApp->GetClipboard());
	pApp->SetSelectedStatement(nullptr);
	pApp->SetClipboard(C);

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
			//pManager->SetClipboard(nullptr);
		}
		else
		{
			c->SetPosition(p);
			c->SetSelected(false);
			pManager->AddStatement(c);
			//pManager->SetClipboard(nullptr);
		}
	}

}

void Conditional::Draw(Output* pOut) const
{
	 	
	pOut->DrawCondition(Top, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}



void Conditional::UpdateStatementText()
{
	
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
	return (P.x >= Top.x - (UI.ASSGN_WDTH / 2) && P.x <= Top.x + (UI.ASSGN_WDTH / 2) &&
		P.y >= Top.y && P.y <= Top.y + UI.ASSGN_HI );
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

bool Conditional::Validate(ApplicationManager* pApp) 
{
	Output* pOut = pApp->GetOutput();

	// LHS variable not declared
	if (!(pApp->IsVariableDeclared(LHS)))
	{
		pOut->PrintMessage("Error: Variable '" + LHS + "' is not declared.");
		return false;
	}
	// statement without incoming connector
	Connector* inConn = getInConnector(0);
	if (inConn == NULL)
	{
		pOut->PrintMessage("Error: Conditional statement must have an incoming connector.");
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
