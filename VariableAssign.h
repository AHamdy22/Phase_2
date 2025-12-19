#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddVariableAssign.h"
#include<fstream>

class VariableAssign : public Statement
{
private:
	string LHS;	
	string RHS;	


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

	virtual void Simulate(ApplicationManager* pManager);

};

#endif

