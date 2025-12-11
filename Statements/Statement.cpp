#include "Statement.h"

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	Text = "";
	Selected = false;	
	IsCopiedFlag = false;
	IsCutFlag = false;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::SetCut(bool c)
{
	IsCutFlag = c;
}

bool Statement::IsCut() const
{
	return IsCutFlag;
}

void Statement::SetCopied(bool c)
{
	IsCopiedFlag = c;
}

bool Statement::IsCopied() const
{
	return IsCopiedFlag;
}

void Statement::GetStatementCut(ApplicationManager* pApp) const
{

}

void Statement::PasteStatement(Statement * D, Point P, Output* pOut, ApplicationManager* pManager) const
{
}

