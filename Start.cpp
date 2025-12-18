#include "Start.h"
#include <fstream>

using namespace std;

Start::Start(Point Lcorner)
{

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet


	Outlet.x = LeftCorner.x + (UI.START_WDTH / 2);
	Outlet.y = LeftCorner.y + UI.START_HI;

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

Point Start::getInlet() const
{
	Point p;
	p.x = -1; // No inlet for Start statement
	p.y = -1;
	return p;
}

Point Start::getOutlet() const
{
	return Outlet;
}

int Start::GetID() const
{
	return ID;
}

string Start::GetText() const
{
	return Text;
}

string Start::GetType() const
{
	return "START";
}

void Start::Save(ofstream& OutFile)
{
	OutFile << "START " << ID << " " << LeftCorner.x << " " << LeftCorner.y << endl;
}


void Start::Move(int x, int y)
{
	LeftCorner.x += x;
	LeftCorner.y += y;

	Outlet.x += x;
	Outlet.y += y;
}
