#ifndef START_H
#define START_H

#include "Statements/Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Start : public Statement
{
private:

	Connector* pOutConn;	//Value Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	void UpdateStatementText();

public:

	Start(Point Lcorner);

	void Draw(Output* pOut) const;

};

#endif
