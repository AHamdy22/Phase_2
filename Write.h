#ifndef WRITE_H
#define WRITE_H

#include "Statements\Statement.h"

class Write : public Statement
{
private:
	string VarName; //The name of the variable to be written write


	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	virtual void UpdateStatementText();

public:
	Write(Point LCorner, string var = "");
	
	string getVar() const;

	void Draw(Output* pOut) const;

	Point getInlet() const;
	Point getOutlet() const;

	bool InStatement(Point p) const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	bool validate(ApplicationManager* pApp) const;
	void Simulate(ApplicationManager* pApp);

	void SetPosition(Point p);
	Point GetPosition() const;
	void GetStatementCut(ApplicationManager* pApp) const;
	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;
	void EditStatement(ApplicationManager* pApp, Point p);
};

#endif