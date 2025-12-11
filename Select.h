#ifndef SELECT_H
#define SELECT_H

#include "Actions\Action.h"

class Select : public Action
{
private:

	Point Position;

public:

	Select(ApplicationManager* pAppManager);

	
	void ReadActionParameters();

	
	void Execute();

};

#endif