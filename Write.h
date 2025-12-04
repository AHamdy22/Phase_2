#ifndef WRITE_H
#define WRITE_H

#include "Statements\Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Write : public Statement
{
private:
	string VarName; //The name of the variable to be written write

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.
	virtual void UpdateStatementText();

public:
	Write(Point LCorner, string var = "");

	void Draw(Output* pOut) const;


};

#endif