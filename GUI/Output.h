#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();	

	window* CreateWind(int, int, int , int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	enum direction { NoDirection, LEFT, RIGHT, UP, DOWN };

	void CreateDesignToolBar();	//Tool bar of the design mode
	
	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar
	
	void ClearDrawArea();	//Clears the drawing area
	
	void ClearOutputBar(); //Clears the Output bar
	
	void ClearDesignToolBar(); //Clears the Design Tool bar after switching to Simulation mode
	
	void ClearSimulationToolBar(); //Clears the Simulation Tool bar after switching to Design mode
	
	void PrintMessage(string msg);	//Prints a message on Status bar
	
	void DrawString(const int, const int, const string);  //Writes a string in the specified location

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected = false);
	
	void DrawDeclare(Point Left, int width, int height, string Text, bool Selected);
	
	void DrawStart(Point Left, int width, int height, string Text, bool Selected);
	
	void DrawEnd(Point Left, int width, int height, string Text, bool Selected);
	
	void DrawRead(Point Left, int width, int height, string Text, bool Selected);
	
	void DrawWrite(Point Left, int width, int height, string Text, bool Selected);
	
	void DrawCondition(Point Top, int width, int height, string Text, bool Selected);
	
	void DrawConnector(Point start, Point end, direction d,bool Selected);
	
	~Output();
};

#endif