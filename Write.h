#ifndef WRITE_H
#define WRITE_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddWrite.h"
#include<fstream>

class Write : public Statement
{
private:
	string VarName; 

	Point Inlet;	 
	
	Point Outlet;	
	

	Point LeftCorner;	
	virtual void UpdateStatementText();

public:
	Write(Point LCorner, string var = "");

	string getVar() const;

	Point getInlet() const;
	Point getOutlet() const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

	bool Validate(ApplicationManager* pApp);
};

#endif