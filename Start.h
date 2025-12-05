#ifndef START_H
#define START_H

#include "Statements/Statement.h"

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
};

#endif
