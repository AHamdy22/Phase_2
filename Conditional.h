#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statements/Statement.h"

class Conditional : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double ValueRHS;	//Right Handside (Value)
	string VariableRHS;	//Right Handside (variable)
	string CompOperator;

	Connector* pOutConn1;	//Value Assignment Stat. has one Connector to next statement
	Connector* pOutConn2;	//Value Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet1;	//A point a connection leaves this statement
	Point Outlet2;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point TopCorner;	//left corenr of the statement block.

	void UpdateStatementText();

public:
	Conditional(Point Tcorner, string LeftHS = "", double ValueRightHS = 0, string VariableRightHS = "", string Operator = "");

	void setLHS(const string& L);
	void setValueRHS(double ValueR);
	void setVariableRHS(string VariableR);
	void setCompOperator(string Operator);

	void Draw(Output* pOut) const;
	bool InStatement(Point P) const;

	Point getInlet() const;
	Point getOutlet1() const;
	Point getOutlet2() const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file
	void Load(ifstream& Infile);	//Load the Statement parameters from a file

};

#endif
