#ifndef DEL_H
#define DEL_H

#include "Actions\Action.h"

class Delete : public Action
{
private:

	Point Position;

	//Position where the user clicks to add the stat.
	//TODO: you should add LHS and RHS of the assignment statement as parameters

public:
	Delete(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();

};

#endif