#ifndef START_H
#define START_H

#include "Statements/Statement.h"

class Start : public Statement
{
private:

	Point Outlet;
	void UpdateStatementText();

public:

	Start(Point Lcorner);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	Point getInlet() const;
	Point getOutlet() const;

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