#ifndef READ_H
#define READ_H

#include "Statements\Statement.h"

class Read : public Statement
{
private:
	string VarName; //The name of the variable to read

	Point LeftCorner;	//left corenr of the statement block.


	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	virtual void UpdateStatementText();

public:
	Read(Point LCorner, string var = "");

	void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const; 

	bool InStatement(Point p) const ; //Checks if a point is inside the statement block

	void Save(ofstream& OutFile);

	int GetID() const;		//returns the statement ID

	string GetText() const;		//returns the statement text

	string GetType() const;	//returns the statement type as a string

	void Load(ifstream& Infile);	//Load the Statement parameters from a file

	void Move(int x, int y);
};

#endif