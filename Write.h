#ifndef WRITE_H
#define WRITE_H

#include "Statements\Statement.h"

class Write : public Statement
{
private:
	string VarName; //The name of the variable to be written write

	Point LeftCorner; // Top-Left corner of the statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	virtual void UpdateStatementText();

public:
	Write(Point LCorner, string var = "");

	void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;

	bool InStatement(Point p) const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file
	void Load(ifstream& Infile);	//Load the Statement parameters from a file

	void Move(int x, int y);
};

#endif