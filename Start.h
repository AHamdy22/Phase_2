#ifndef START_H
#define START_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"
#include"Actions\..\AddStart.h"
#include<fstream>

class Start : public Statement
{
private:

	Connector* pOutConn;	
	Point Outlet;	
	Point LeftCorner;
	static int CountStart;

	void UpdateStatementText();

public:

	Start(Point Lcorner);

	void Draw(Output* pOut) const;

	bool InStatement(Point P) const;

	virtual Point GetPosition() const;

	virtual void SetPosition(Point p);

	void EditStatement(ApplicationManager* pApp, Point p);

	void GetStatementCut(ApplicationManager* pApp) const;

	virtual void PasteStatement(Statement* S, Point P, Output* pOut, ApplicationManager* pManager) const;

	Point getInlet() const;
	Point getOutlet() const;

	int GetID() const;				//returns the statement ID
	string GetText() const;			//returns the statement text
	string GetType() const;			//returns the statement type as a string

	void Save(ofstream& OutFile); 	//Save the Statement parameters to a file

	void Move(int x, int y);

	bool Validate(ApplicationManager* pApp);

	~Start();
};

#endif