#ifndef ADD_READ_H
#define ADD_READ_H

#include "Actions\Action.h"
#include "Statements\..\Read.h"


class AddRead : public Action
{
private:
	string VarName;	//The name of the variable to read into

	Point Position;	//Position where the user clicks to add the stat.
	

public:
	AddRead(ApplicationManager* pAppManager);

	//Read Read statements position
	void ReadActionParameters();

	//Create and add a read statement to the list of statements
	void Execute();

};

#endif