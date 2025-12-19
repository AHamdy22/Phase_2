#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddConditional.h"


class Conditional : public Statement
{
private:
	string LHS;	
	double ValueRHS;	
	string VariableRHS;	//Right Handside (variable)
	string CompOperator;

	Connector* pNoConn;
	Connector* pYesConn;	
	
	Point Inlet;		//A point where connections enters this statement 

	Point YesOutlet;	// A point where "Yes" connections leaves this statement
	Point NoOutlet;	    // A point where "No" connections leaves this statement
	
		
	Point Top;	

	void UpdateStatementText();

public:
	Conditional(Point T, string LeftHS = "", double ValueRightHS = 0, string VariableRightHS = "", string Operator = "");

	void setLHS(const string& L);
	void setValueRHS(double ValueR);
	void setVariableRHS(string VariableR);
	void setCompOperator(string Operator);

	Point getInlet() const;
	Point getOutlet() const;
	Point getYesOutlet() const;
	Point getNoOutlet() const;

	void setNoConnector(Connector* pConn);			// Set the No connector
	Connector* getNoConnector() const;				// Get the No connector

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	void Draw(Output* pOut) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

	bool InStatement(Point P) const;

	bool Validate(ApplicationManager* pApp);

	virtual void Simulate(ApplicationManager* pApp);
};

#endif

