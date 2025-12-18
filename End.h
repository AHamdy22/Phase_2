#ifndef END_H
#define END_H

#include "Statements/Statement.h"
#include "ApplicationManager.h"

class End : public Statement
{
private:

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors

	Point LeftCorner;		//Top-Left corner of the statement

	static int CountEnd;

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
	void Load(ifstream& Infile);	//Load the Statement parameters from a file

	void Move(int x, int y);

	~End();

	bool validate(ApplicationManager* pApp) const;

};

#endif