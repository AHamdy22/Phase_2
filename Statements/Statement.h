#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
#include "..\GUI\Output.h"

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	static int NextID; //Static variable to hold the next ID to be assigned

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	Point LeftCorner;	//left corenr of the statement block.

	/// Add more parameters if needed.
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Connector* pOutConn;              // Outgoing connector from this statement
	Connector* pInConnList[3];		  // Array of incoming connectors 
	int ConnCount;

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual bool InStatement(Point P) const = 0;
	

	virtual Point getInlet() const = 0;		//returns the inlet point
	virtual Point getOutlet() const = 0;	//returns the outlet point

	virtual string GetType() const = 0;		//returns the statement type as a string
	virtual int GetID() const = 0;			//returns the statement ID
	virtual string GetText() const = 0;		//returns the statement text

	virtual void Save(ofstream& OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream& Infile) = 0;	//Load the Statement parameters from a file

	// Functions to manage connectors
	void setOutConnector(Connector* pConn);			// Set the outgoing connector
	Connector* getOutConnector() const;				// Get the outgoing connector
	void addInConnector(Connector* pConn);			// Add an incoming connector
	Connector* getInConnector(int index) const;		// Get an incoming connector by index
	int getInConnectorCount() const;				// Get the number of incoming connectors

	void Move(int x, int y); 						// Move the statement by x and y to make all the connectors vertical

};

#endif