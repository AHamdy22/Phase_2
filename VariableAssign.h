#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statements\Statement.h"


class VariableAssign : public Statement
{
private:
	string LHS;	
	string RHS;	

	Connector* pOutConn;	

	Point Inlet;	
	Point Outlet;	
	Point LeftCorner;	


	int stringlength;

	int stringheight;


	virtual void UpdateStatementText();

public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS(const string& R);

	virtual void Draw(Output* pOut) const;

};

#endif

