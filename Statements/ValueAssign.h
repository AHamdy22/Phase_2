#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"
#include "..\ApplicationManager.h"
#include<fstream>

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)

	Point LeftCorner;		//Top-Left corner of the statement

	Point Inlet;	//A point where connections enters this statement
	Point Outlet;	//A point a connection leaves this statement


	void UpdateStatementText();

public:
	ValueAssign(Point Lcorner, string LeftHS = "", double RightHS = 0);

	void setLHS(const string& L);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;
	bool InStatement(Point p) const;
	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string
	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file
	void Load(ifstream& Infile);	//Load the Statement parameters from a file

	void Move(int x, int y);

	bool validate(ApplicationManager* pApp) const;

};

#endif