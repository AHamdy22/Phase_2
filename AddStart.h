#ifndef ADD_START_H
#define ADD_START_H

#include "Actions\Action.h"
#include "Statements\..\Start.h"

class AddStart : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.

public:
	AddStart(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();

};

#endif