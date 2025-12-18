#ifndef DECLARE_H
#define DECLARE_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"

class Declare : public Statement
{
private:
	string DataType;
	string Var;


	Point Inlet;
	Point Outlet;



	virtual void UpdateStatementText();

public:
	Declare(Point Lcorner, string data_type = "", string Variable = "");

	void setDataType(const string& d);
	void setVar(const string& v);
	string getVar() const;
	bool InStatement(Point p) const;

	virtual Point GetPosition() const;
	virtual void SetPosition(Point p);

	virtual void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;

	int GetID() const;
	string GetText() const;
	string GetType() const;

	void Save(ofstream& OutFile);

	void Move(int x, int y);

	bool validate(ApplicationManager* pApp) const;
};

#endif