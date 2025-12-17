#ifndef END_H
#define END_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddEnd.h"

class End : public Statement
{
private:

	Point Inlet;	

	Point LeftCorner;	

	void UpdateStatementText();

public:

	End(Point Lcorner);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

};

#endif