#include "Write.h"

void Write::UpdateStatementText()
{
	Text = "Write " + VarName;
}

Write::Write(Point LCorner, string var)
{
	VarName = var;
	UpdateStatementText();
	LeftCorner = LCorner;
	Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READ_HI;
}

void Write::Draw(Output* pOut) const
{
	pOut->DrawWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}