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
	static int NextID; //Static variable to hold the next ID to be assigned
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	Connector* pOutConn;	//A pointer to the outgoing connector
	Point LeftCorner; // Top-Left corner of the statement(Top corner point in case of conditional statement)
	bool IsCutFlag;    //true if the statement is cut
	bool IsCopiedFlag; //true if the statement is copied

	Connector* pInConnList[2];		  // Array of incoming connectors 
	int ConnCount;                    // Number of connectors

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

public:
	Statement();
	void SetID(int id);
	void SetSelected(bool s);
	bool IsSelected() const;

	void SetCut(bool c);
	bool IsCut() const;
	void SetCopied(bool c);
	bool IsCopied() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual bool InStatement(Point P) const = 0;
	virtual Point getInlet() const = 0;		//returns the inlet point
	virtual Point getOutlet() const = 0;	//returns the outlet point
	virtual void GetStatementCut(ApplicationManager* pApp) const = 0;
	virtual void PasteStatement(Statement* D, Point P, Output* pOut, ApplicationManager* pManager) const = 0;
	

	virtual string GetType() const = 0;		//returns the statement type as a string
	virtual int GetID() const = 0;			//returns the statement ID
	virtual string GetText() const = 0;		//returns the statement text

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	
	virtual void EditStatement(ApplicationManager* pApp, Point p) = 0;		//Edit the Statement parameter

	virtual Point GetPosition() const = 0;

	virtual void SetPosition(Point p) = 0;

	virtual bool Validate(ApplicationManager* pApp) = 0;

	virtual void Simulate(ApplicationManager* pManager);	//Execute the statement in the simulation mode

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

	double getLeftCornerY() const;		// Get the top-left corner point of the statement

	// Functions to manage connectors
	void setOutConnector(Connector* pConn);			// Set the outgoing connector
	Connector* getOutConnector() const;				// Get the outgoing connector
	void addInConnector(Connector* pConn);			// Add an incoming connector
	Connector* getInConnector(int index) const;		// Get an incoming connector by index
	int getInConnectorCount() const;				// Get the number of incoming connectors

	virtual void Move(int x, int y) = 0; 			// Move the statement by x and y to make all the connectors vertical

};

#endif