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

	Point getInlet() const;
	Point getOutlet() const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file
	void Load(ifstream& Infile);	//Load the Statement parameters from a file
};

#endif
