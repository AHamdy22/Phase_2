#include "Declare.h"
#include <sstream>


using namespace std;

Declare::Declare(Point Lcorner, string data_type, string variable)
{

	DataType = data_type;
	Var = variable;

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

void Declare::setDataType(const string& d)
{
	DataType = d;
	UpdateStatementText();
}

void Declare::setVar(const string& v)
{
	Var = v;
	UpdateStatementText();
}

bool Declare::InStatement(Point P) const
{

	return (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI);
}

Point Declare::GetPosition() const
{
	return LeftCorner;
}

void Declare::SetPosition(Point p)
{
	LeftCorner = p;
}

void Declare::EditStatement(ApplicationManager* pApp, Point p)
{

	AddDeclare* D = new AddDeclare(pApp);

	D->SetPosition(p);

	D->ReadActionParameters();

	DataType = D->GetDataType();

	Var = D->GetVar();

	UpdateStatementText();

	delete D;
}

void Declare::Draw(Output* pOut) const
{

	pOut->DrawDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}



void Declare::UpdateStatementText()
{

	ostringstream T;
	T << DataType << " " << Var;
	Text = T.str();
}