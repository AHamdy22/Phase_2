#ifndef WRITE_H
#define WRITE_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddWrite.h"

class Write : public Statement
{
private:
	string VarName; 

	Point Inlet;	 
	
	Point Outlet;	
	

	Point LeftCorner;	
	virtual void UpdateStatementText();

public:
	Write(Point LCorner, string var = "");

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

};

#endif