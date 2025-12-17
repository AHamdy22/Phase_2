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

	Connector* pOutConn1;	
	Connector* pOutConn2;	
	


	Point Inlet;	
	Point Outlet1;	
	Point Outlet2;	
	

	Point Top;	

	void UpdateStatementText();

public:
	Conditional(Point T, string LeftHS = "", double ValueRightHS = 0, string VariableRightHS = "", string Operator = "");

	void setLHS(const string& L);
	void setValueRHS(double ValueR);
	void setVariableRHS(string VariableR);
	void setCompOperator(string Operator);

	void Draw(Output* pOut) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

	bool InStatement(Point P) const;

};

#endif

