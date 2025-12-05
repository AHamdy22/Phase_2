#ifndef END_H
#define END_H

#include "Statements/Statement.h"

class End : public Statement
{
private:

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors

	Point LeftCorner;	//left corenr of the statement block.

	void UpdateStatementText();

public:

	End(Point Lcorner);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;
};

#endif


