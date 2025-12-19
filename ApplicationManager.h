#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Var_info.h"
#include "Statements\Statement.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement *pSelectedStat; //a pointer to the last selected statement
	Connector* pSelectedConn;
	Statement *pClipboard;    //a pointer to the last copied/cut statement
	                          //you can set and get this pointer

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	Var_info VarList[MaxCount];			// Array to store variables
	int VarCount;						// Number of variables

	bool validated;						// Indicates whether the flowchart has been validated or not
	Statement* pNextStat;				//A pointer to the next statement to be executed used in simulation mode

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// == Actions Related Functions ==
	ActionType GetUserAction() const; //Reads the input command from the user 
	                                  //and returns the corresponding action type
	void ExecuteAction(ActionType) ;  //Creates an action and executes it
	
	// == Statements/Connector Management Functions ==
	void AddStatement(Statement* pStat);    //Adds a new Statement to the Flowchart
	Statement* GetStatement(Point p) const;   // Searches for a statement where point P belongs
	Statement* GetStatement(int index) const; // Searches for a statement by index

	int GetStatementCount() const;        //Returns the actual number of statements

	void AddConnector(Connector* pConn);    //Adds a new Connector to the Flowchart
	Connector *GetConnector(int index) const;		// Search for a Connector by index
	Connector* GetConnector(Point P) const;			// Search for a Connector where point P belongs

	int GetConnectorCount() const;        //Returns the actual number of connectors

	// Note: you should use the following 4 functions 
	//       in order not to break class responsibilities (especially in copy, cut and paste)
	Statement *GetSelectedStatement() const;	 //Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	Connector* GetSelectedConnector() const;
	void SetSelectedConnector(Connector* pStat);
	void DeleteConnector(Connector* pStat);
	void DeleteStatement(Statement* pStat);
	Statement *GetClipboard() const;	         //Returns the Clipboard
	void SetClipboard(Statement *pStat);         //Set the Clipboard


	// == Interface Management Functions ==
	Input *GetInput() const;        //Return pointer to the input
	Output *GetOutput() const;      //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	void ClearAll();                //Clears all statements and connectors from the flowchart

	
	// Functions used in validation
	void DeclareVariable(string varName);
	void SetVariableValue(string varName, double value);
	double GetVariableValue(string varName); // You must check if the variable is declared and initialized before calling this function
	bool IsVariableDeclared(string varName);
	bool IsVariableInitialized(string varName);
	void SetVariableInitialized(string varName, bool initialized);
	int FindVariable(string varName);
	void ClearVariables();
	int GetStartCount() const;
	int GetEndCount() const;

	void setValidated(bool val);
	bool isValidated() const;

	void SetNextStatement(Statement* pStat);
	Statement* GetNextStatement() const;
};

#endif