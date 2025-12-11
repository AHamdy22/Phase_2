#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddOperatorAssign.h"


class OperatorAssign : public Statement
{
private:
	string LHS;
	string varOP1;
	double valOP1;
	string varOP2;
	double valOP2;
	char Operation;

	Connector* pOutConn;

	Point Inlet;
	Point Outlet;
	Point LeftCorner;


	int stringlength;

	int stringheight;


	virtual void UpdateStatementText();

public:
	OperatorAssign(Point Lcorner, string LeftHS = "", double valop1 = 0, string varop1 = "", double valop2 = 0, string varop2 = "", char arthop = '+');

	void setLHS(const string& L);
	void setvarOP1(const string& o1);
	void setvalOP1(double p1);
	void setvarOP2(const string& o2);
	void setvalOP2(double p2);

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	virtual void Draw(Output* pOut) const;

};

#endif



