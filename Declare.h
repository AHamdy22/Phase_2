#ifndef DECLARE_H
#define DECLARE_H

#include "Statements\Statement.h"


class Declare : public Statement
{
private:
	string DataType;
	string Var;

	Connector* pOutConn;	

	
	Point Inlet;	
	Point Outlet;	

	Point LeftCorner;


	int stringlength;

	int stringheight;


	virtual void UpdateStatementText();

public:
	Declare(Point Lcorner, string data_type = "", string Variable = "");

	void setDataType(const string& d);
	void setVar(const string& v);

	virtual void Draw(Output* pOut) const;

};

#endif

