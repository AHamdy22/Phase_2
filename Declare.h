#ifndef DECLARE_H
#define DECLARE_H


#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddDeclare.h"

class Declare : public Statement
{
private:

	string Var;

	Connector* pOutConn;	

	
	Point Inlet;	
	Point Outlet;	

	Point LeftCorner;


	int stringlength;

	int stringheight;


	virtual void UpdateStatementText();

public:
	Declare(Point Lcorner, string Variable = "");

	
	void setVar(const string& v);

	bool InStatement(Point p) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;
	
	virtual void Draw(Output* pOut) const;


};

#endif

