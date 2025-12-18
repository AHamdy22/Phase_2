#ifndef START_H
#define START_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"

class Start : public Statement
{
private:


	Point LeftCorner;		//Top-Left corner of the statement

	Point Outlet;

	static int CountStart;

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
	void Load(ifstream& Infile);	//Load the Statement parameters from a file

	void Move(int x, int y);

	~Start();

	bool validate(ApplicationManager* pApp) const;

};

#endif