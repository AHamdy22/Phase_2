#ifndef END_H
#define END_H

#include "Statements/Statement.h"

class End : public Statement
{
private:

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors


	void UpdateStatementText();

public:

	End(Point Lcorner);

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