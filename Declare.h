#ifndef DECLARE_H
#define DECLARE_H


#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddDeclare.h"

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
	bool InStatement(Point p) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	virtual void Draw(Output* pOut) const;


};

#endif

