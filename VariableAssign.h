#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddVariableAssign.h"

class VariableAssign : public Statement
{
private:
	string LHS;
	string RHS;


	Point Inlet;
	Point Outlet;


	int stringlength;

	int stringheight;


	virtual void UpdateStatementText();

public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS(const string& R);

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);


	virtual void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;
	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string
	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	bool validate(ApplicationManager* pApp) const;
	void Simulate(ApplicationManager* pApp);

	void GetStatementCut(ApplicationManager* pApp) const;
	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;
	void EditStatement(ApplicationManager* pApp, Point p);

};

#endif
