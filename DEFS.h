#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_DECLARE_VARIABLE, // Add  declare variable statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements
	
	ADD_END,   //Add end statement
	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	EXIT,		//Exit the application


	VALIDATE,
	RUN,
	SWITCH_DSN_MODE,	//Switch to Design mode


	DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	SIM_TOOL,	   //A click on an empty place in the simulation tool bar
	STATUS 		   //A click on the status bar
};

enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_START,		//Start statement
	ITM_DECLARE,	//Declare variable statement
	ITM_VALUE_ASSIGN,//simple assignment statement
	ITM_VARIABLE_ASSIGN,//variable assignment statement
	ITM_OPERATOR_ASSIGN,//operator assignment statement
	ITM_COND,		//conditional statement
	ITM_READ,		//Read statement
	ITM_WRITE,		//Write statement
	ITM_CONNECTOR,	//Connector
	ITM_END,		//End statement
	ITM_SELECT,		//Select
	ITM_EDIT,		//Edit
	ITM_DELETE,		//Delete
	ITM_COPY,		//Copy
	ITM_CUT,		//Cut
	ITM_PASTE,		//Paste
	ITM_SWITCH_TO_SIM, //Switch to Simulation
	ITM_SAVE,		//Save
	ITM_LOAD,		//Load
	ITM_EXIT1,		//Exit
	

	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};

enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run
	ITM_SWITCH_TO_DESIGN, //Switch to Design
	ITM_EXIT2,		//Exit
	
	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif