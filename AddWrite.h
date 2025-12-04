#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Actions\Action.h"
#include "Statements\..\Write.h"


class AddWrite : public Action
{
private:
	string VarName;	//The name of the variable to be written

	Point Position;	//Position where the user clicks to add the stat.

	string TXTEntered; //The text to be written


public:
	AddWrite(ApplicationManager* pAppManager);

	//Read Read statements position
	void ReadActionParameters();

	//Create and add a read statement to the list of statements
	void Execute();

};

#endif