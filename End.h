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

	Point getInlet() const;
	Point getOutlet() const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file
	void Load(ifstream& Infile);	//Load the Statement parameters from a file
};

#endif


