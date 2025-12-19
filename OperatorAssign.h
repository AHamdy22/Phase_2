#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddOperatorAssign.h"
#include<fstream>

class OperatorAssign : public Statement
{
private:
	string LHS;
	string varOP1;
	double valOP1;
	string varOP2;
	double valOP2;
	char Operation;

	

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

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

	virtual void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;
	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string
	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	bool Validate(ApplicationManager* pApp);

};

#endif



