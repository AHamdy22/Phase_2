#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statements/Statement.h"

class Conditional : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double ValueRHS;	//Right Handside (Value)
	string VariableRHS;	//Right Handside (variable)
	string CompOperator;	//Comparison Operator

	Point Inlet;	//A point where connections enters this statement 
	
	Point YesOutlet;	// A point where "Yes" connections leaves this statement
	Point NoOutlet;	    // A point where "No" connections leaves this statement

	// pYesConn is the pOutConn
	Connector* pNoConn;


	void UpdateStatementText();

public:
	Conditional(Point Tcorner, string LeftHS = "", double ValueRightHS = 0, string VariableRightHS = "", string Operator = "");

	void setLHS(const string& L);
	void setValueRHS(double ValueR);
	void setVariableRHS(string VariableR);
	void setCompOperator(string Operator);
	
	string getLHS() const;
	string getVariableRHS() const;

	void Draw(Output* pOut) const;
	bool InStatement(Point P) const;

	Point getInlet() const;
	Point getOutlet() const;
	Point getYesOutlet() const;
	Point getNoOutlet() const;

	// Let setOutConnector & getOutConnector be for Yes connector
	void setNoConnector(Connector* pConn);			// Set the No connector
	Connector* getNoConnector() const;				// Get the No connector

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	bool validate(ApplicationManager* pApp) const;
};

#endif