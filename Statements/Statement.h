#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
#include "..\ApplicationManager.h"
//class Output;
#include "..\GUI\Output.h"

// Forward declaration to fix C2061 error
class ApplicationManager;

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	bool IsCutFlag;    //true if the statement is cut
	bool IsCopiedFlag; //true if the statement is copied


	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	void SetCut(bool c);
	bool IsCut() const;
	void SetCopied(bool c);
	bool IsCopied() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual bool InStatement(Point P) const = 0;
	virtual void GetStatementCut(ApplicationManager* pApp) const;
	virtual void PasteStatement(Statement* D, Point P, Output* pOut, ApplicationManager* pManager) const;
	
	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	//virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	//virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void EditStatement(ApplicationManager* pApp, Point p) = 0;		//Edit the Statement parameter

	virtual Point GetPosition() const = 0;

	virtual void SetPosition(Point p) = 0;

	//virtual void Simulate();	//Execute the statement in the simulation mode

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

};

#endif