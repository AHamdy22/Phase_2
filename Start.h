#ifndef START_H
#define START_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddStart.h"

class Start : public Statement
{
private:

	Connector* pOutConn;	
	Point Outlet;	
	Point LeftCorner;
	void UpdateStatementText();

public:

	Start(Point Lcorner);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);
};

#endif